/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:14:34 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:27:03 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_envlst	*remove_env_node(t_envlst *env_list)
{
	t_envlst	*next;

	next = env_list->next;
	free(env_list->key);
	if (env_list->value)
		free(env_list->value);
	free(env_list);
	return (next);
}

static void	handle_unset_error(char *str, int *error_flag)
{
	if (ft_isdigit(str[0]))
	{
		ft_putstr_fd("minishell: unset: \'", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
		*error_flag = 1;
	}
}

static int	env_var(t_info *info, t_envlst *cur, t_envlst *prev, char *str)
{
	if (ft_strlen(cur->key) == ft_strlen(str) \
	&& ft_strncmp(cur->key, str, ft_strlen(str)) == 0)
	{
		if (ft_strncmp(cur->key, "PATH", 4) == 0)
		{
			free_all(info->path_list);
			info->path_list = NULL;
		}
		if (prev == NULL)
			info->env_list = remove_env_node(cur);
		else
			prev->next = remove_env_node(cur);
		return (1);
	}
	return (0);
}

int	mini_unset(t_info *info, char **av)
{
	t_envlst	*cur;
	t_envlst	*prev;
	int			idx;
	int			error_flag;

	idx = 0;
	error_flag = 0;
	while (av[++idx])
	{
		handle_unset_error(av[idx], &error_flag);
		cur = info->env_list;
		prev = NULL;
		while (cur)
		{
			if (env_var(info, cur, prev, av[idx]))
				break ;
			prev = cur;
			cur = cur->next;
		}
	}
	return (error_flag);
}
