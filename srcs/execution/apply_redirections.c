/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:55 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:38:09 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_inputfile_fd(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
	{
		mini_error(infile, NULL);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	set_heredoc_fd(int num)
{
	int		fd;
	char	*file_cnt;
	char	*file_name;

	file_cnt = ft_itoa(num);
	file_name = ft_strjoin(file_cnt, ".tmp");
	fd = open(file_name, O_RDONLY);
	free_all_str(file_cnt, file_name, NULL, NULL);
	if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
	{
		mini_error("heredoc", file_name);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	set_overwrite_fd(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		mini_error(outfile, NULL);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	set_append_fd(char *outfile)
{
	int	fd;

	fd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		mini_error(outfile, NULL);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirections(t_cmd *cmd_list, int cnt)
{
	t_redir	*cur;
	int		result;

	cur = cmd_list->redir;
	while (cur)
	{
		if (ft_strncmp(cur->type, "<<", 2) == 0)
			result = set_heredoc_fd(cnt);
		else if (ft_strncmp(cur->type, "<", 1) == 0)
			result = set_inputfile_fd(cur->file);
		else if (ft_strncmp(cur->type, ">>", 2) == 0)
			result = set_append_fd(cur->file);
		else if (ft_strncmp(cur->type, ">", 1) == 0)
			result = set_overwrite_fd(cur->file);
		if (result == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
