/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:03:46 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:39:13 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_single_cmd_child(t_info *info, t_cmd *cmd_list)
{
	char	*file;

	if (apply_redirections(cmd_list, 0) == -1)
	{
		g_termination_status = 1;
		exit(g_termination_status);
	}
	if (cmd_list->argv == NULL)
		exit(g_termination_status);
	file = find_execute_path(cmd_list->argv[0], info->path_list);
	if (file == NULL)
		handle_command_not_found_error(info->path_list, cmd_list->argv[0]);
	execve(file, cmd_list->argv, env_list_to_envp(info->env_list));
	mini_error("execve", NULL);
	g_termination_status = 1;
	exit(g_termination_status);
}

void	execute_single_cmd(t_info *info, t_cmd *cmd_list)
{
	pid_t	pid;

	if (!check_builtin(info, cmd_list, 0))
	{
		pid = fork();
		if (pid < 0)
			mini_error("fork", NULL);
		else if (pid == 0)
		{
			signal(SIGINT, sighandler_quit);
			signal(SIGQUIT, sighandler_quit);
			run_single_cmd_child(info, cmd_list);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			wait(&(g_termination_status));
			if (WIFSIGNALED(g_termination_status))
				g_termination_status = 128 + WTERMSIG(g_termination_status);
			if (WIFEXITED(g_termination_status))
				g_termination_status = WEXITSTATUS(g_termination_status);
		}
	}
}
