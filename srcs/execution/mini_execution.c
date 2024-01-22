/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:26:22 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:38:53 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execute_builtin(t_info *info, t_cmd *cmd_list, int cnt)
{
	if (apply_redirections(cmd_list, cnt) == -1)
	{
		g_termination_status = 1;
		return (0);
	}
	dup2(info->stdin, STDIN_FILENO);
	if (ft_strncmp(cmd_list->argv[0], "cd", 2) == 0)
		g_termination_status = mini_cd(info, cmd_list->argv);
	if (ft_strncmp(cmd_list->argv[0], "echo", 4) == 0)
		g_termination_status = mini_echo(cmd_list->argv);
	if (ft_strncmp(cmd_list->argv[0], "env", 3) == 0)
		g_termination_status = mini_env(info->env_list);
	if (ft_strncmp(cmd_list->argv[0], "exit", 4) == 0)
		g_termination_status = mini_exit(info, cmd_list);
	if (ft_strncmp(cmd_list->argv[0], "export", 6) == 0)
		g_termination_status = mini_export(info, cmd_list->argv);
	if (ft_strncmp(cmd_list->argv[0], "pwd", 3) == 0)
		g_termination_status = mini_pwd();
	if (ft_strncmp(cmd_list->argv[0], "unset", 5) == 0)
		g_termination_status = mini_unset(info, cmd_list->argv);
	dup2(info->stdout, STDOUT_FILENO);
	return (1);
}

char	*find_execute_path(char *cmd, char **path_list)
{
	char	*cmd_file;
	char	*temp;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	temp = ft_strjoin("/", cmd);
	while (path_list && *path_list)
	{
		cmd_file = ft_strjoin(*path_list, temp);
		if (access(cmd_file, X_OK) == 0)
		{
			free(temp);
			return (cmd_file);
		}
		free(cmd_file);
		path_list++;
	}
	free(temp);
	return (NULL);
}

void	handle_command_not_found_error(char **path_list, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (path_list)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	g_termination_status = 127;
	exit(g_termination_status);
}

int	check_builtin(t_info *info, t_cmd *cmd_list, int cnt)
{
	char	*cmd;

	if (cmd_list->argv == NULL)
		return (0);
	cmd = cmd_list->argv[0];
	if ((ft_strlen(cmd) == 2 && ft_strncmp(cmd, "cd", 2) == 0) \
		|| (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "echo", 4) == 0) \
		|| (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "env", 3) == 0) \
		|| (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "exit", 4) == 0) \
		|| (ft_strlen(cmd) == 6 && ft_strncmp(cmd, "export", 6) == 0) \
		|| (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "pwd", 3) == 0) \
		|| (ft_strlen(cmd) == 5 && ft_strncmp(cmd, "unset", 5) == 0))
		return (execute_builtin(info, cmd_list, cnt));
	return (0);
}

void	mini_execution(t_info *info, t_cmd *cmd_list)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mini_error("fork", NULL);
		g_termination_status = 1;
		return ;
	}
	else if (pid == 0)
		execute_heredoc(info, cmd_list);
	signal(SIGINT, SIG_IGN);
	wait(&g_termination_status);
	if (WIFEXITED(g_termination_status))
		g_termination_status = WEXITSTATUS(g_termination_status);
	if (WIFSIGNALED(g_termination_status))
		g_termination_status = 1;
	else
	{
		if (cmd_list->next)
			execute_another_cmd(info, cmd_list);
		else
			execute_single_cmd(info, cmd_list);
	}
	unlink_heredoc_files(cmd_list);
}
