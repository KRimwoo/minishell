/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:14:22 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/21 15:58:08 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_error(char *str1, char *str2)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
	}
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	free_all(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

char	**env_list_to_envp(t_envlst *env_list)
{
	char		**envp;
	int			cnt;
	t_envlst	*tmp;

	cnt = 0;
	tmp = env_list;
	while (tmp)
	{
		cnt++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!envp)
		return (NULL);
	cnt = 0;
	while (env_list)
	{
		envp[cnt] = ft_strjoin(env_list->key, "=");
		if (env_list->value)
			envp[cnt] = ft_strjoin(envp[cnt], env_list->value);
		env_list = env_list->next;
		cnt++;
	}
	envp[cnt] = NULL;
	return (envp);
}
