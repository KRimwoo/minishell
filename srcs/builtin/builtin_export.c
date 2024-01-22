/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:03:32 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:26:30 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_env_val(t_info *info, char *key, char *val)
{
	t_envlst	*cur;

	cur = info->env_list;
	while (cur)
	{
		if (ft_strlen(cur->key) == ft_strlen(key) \
		&& ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
		{
			if (ft_strncmp(key, "PATH", 4) == 0)
			{
				free_all(info->path_list);
				info->path_list = ft_split(val, ':');
			}
			if (val)
			{
				if (cur->value)
					free(cur->value);
				cur->value = ft_strdup(val);
			}
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

static void	display_env_list(t_envlst *env_list)
{
	while (env_list)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_list->key, STDOUT_FILENO);
		if (env_list->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_list->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		env_list = env_list->next;
	}
}

static int	is_vaild_env_key(char *key)
{
	int	idx;

	idx = 0;
	if (ft_isalpha(key[0]) == 0 && key[0] != '_')
		return (0);
	while (key[++idx])
		if (ft_isalnum(key[idx]) == 0 && key[idx] != '_')
			return (0);
	return (1);
}

static int	handle_invaild_key(t_envlst *env_node, char *str, int *error_flag)
{
	char	*key;

	key = env_node->key;
	if (!is_vaild_env_key(key))
	{
		ft_putstr_fd("minishell: export: \'", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
		free_envlst(env_node);
		*error_flag = 1;
		return (1);
	}
	return (0);
}

int	mini_export(t_info *info, char **av)
{
	int			idx;
	int			flag_error;
	t_envlst	*new;

	idx = 0;
	flag_error = 0;
	while (av[++idx])
	{
		if (av[idx][0] == '\0')
			continue ;
		new = create_env_node(av[idx]);
		if (handle_invaild_key(new, av[idx], &flag_error))
			continue ;
		else if (update_env_val(info, new->key, new->value))
			free_envlst(new);
		else
		{
			if (ft_strncmp(new->key, "PATH", 4) == 0)
				info->path_list = ft_split(new->value, ':');
			add_envlst(&info->env_list, new);
		}
	}
	if (idx == 1)
		display_env_list(info->env_list);
	return (flag_error);
}
