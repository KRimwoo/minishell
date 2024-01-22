/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:25:58 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:22:28 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setting_pwd(t_info *info, char *key)
{
	char	**av;
	char	current_working_dir[1024];

	av = malloc(sizeof(char *) * 3);
	if (!av)
		return ;
	getcwd(current_working_dir, 1024);
	av[0] = ft_strdup("export");
	av[1] = ft_strjoin(key, current_working_dir);
	av[2] = 0;
	mini_export(info, av);
	free_all(av);
}

int	mini_cd(t_info *info, char **av)
{
	char	*path;

	setting_pwd(info, "OLDPWD=");
	if (av[1] && (access(av[1], F_OK) || chdir(av[1])))
	{
		mini_error("cd", av[1]);
		return (1);
	}
	if (av[1] == NULL)
	{
		path = get_envval(info->env_list,
				ft_strdup("HOME"));
		if (path[0] == '\0')
		{
			free(path);
			ft_putendl_fd("minishell: cd: HOME not setting", STDERR_FILENO);
			return (1);
		}
		chdir(path);
		free(path);
	}
	setting_pwd(info, "PWD=");
	return (0);
}
