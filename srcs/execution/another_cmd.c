/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:28:04 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:37:22 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setting_io_fd(t_cmd *cmd_list)
{
	if (cmd_list->prev && dup2(cmd_list->prev->pipe[0], STDIN_FILENO) == -1)
	{
		g_termination_status = 1;
		exit(g_termination_status);
	}
	if (cmd_list->next)
	{
		close(cmd_list->pipe[0]);
		if (dup2(cmd_list->pipe[1], STDOUT_FILENO) == -1)
		{
			g_termination_status = 1;
			exit(g_termination_status);
		}
	}
}

static void	run_another_cmd_child(t_info *info, t_cmd *cmd_list, int cnt)
{
	char	*file;

	signal(SIGINT, sighandler_quit);
	signal(SIGQUIT, sighandler_quit);
	setting_io_fd(cmd_list);
	if (check_builtin(info, cmd_list, cnt))
		exit(g_termination_status);
	else
	{
		if (apply_redirections(cmd_list, cnt) == -1)
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
}

static void	wait_and_set_exit_status(pid_t pid, int cnt)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &g_termination_status, 0);
	while (--cnt)
		wait(0);
	if (WIFSIGNALED(g_termination_status))
		g_termination_status = 128 + WTERMSIG(g_termination_status);
	if (WIFEXITED(g_termination_status))
		g_termination_status = WEXITSTATUS(g_termination_status);
}

void	execute_another_cmd(t_info *info, t_cmd *cmd_list)
{
	int		cnt;
	pid_t	pid;

	cnt = 0;
	while (cmd_list)
	{
		if (cmd_list->next && pipe(cmd_list->pipe) == -1)
		{
			mini_error("pipe", NULL);
			return ;
		}
		if (cmd_list->prev)
			close(cmd_list->prev->pipe[1]);
		pid = fork();
		if (pid < 0)
			mini_error("fork", NULL);
		else if (pid == 0)
			run_another_cmd_child(info, cmd_list, cnt);
		if (cmd_list->prev)
			close(cmd_list->prev->pipe[0]);
		cmd_list = cmd_list->next;
		cnt++;
	}
	wait_and_set_exit_status(pid, cnt);
}
