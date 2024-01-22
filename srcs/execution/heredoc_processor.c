/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:45:34 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:38:26 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_value_if(t_envlst *env_list, char *str,
	int *cur_idx, int *next_idx)
{
	*next_idx = *cur_idx + 1;
	if (str[*next_idx] == '?')
	{
		*next_idx += 1;
		return (ft_itoa(g_termination_status));
	}
	if (str[*next_idx] == '\0' || !ft_isalnum(str[*next_idx]))
		return (NULL);
	while (str[*next_idx]
		&& (ft_isalnum(str[*next_idx]) || str[*next_idx] == '_'))
		*next_idx += 1;
	return (get_envval(env_list,
			ft_substr(str, *cur_idx + 1, *next_idx - *cur_idx - 1)));
}

static void	process_heredoc_env(t_envlst *env_list, int fd, char *str)
{
	int		start_idx;
	int		end_idx;
	char	*env_value;

	start_idx = 0;
	end_idx = 0;
	while (str[end_idx])
	{
		if (str[end_idx] == '$')
		{
			write(fd, str + start_idx, end_idx - start_idx);
			start_idx = end_idx;
			env_value = get_env_value_if(env_list, str, &start_idx, &end_idx);
			if (env_value)
			{
				write(fd, env_value, ft_strlen(env_value));
				start_idx = end_idx;
				free(env_value);
			}
		}
		else
			end_idx++;
	}
	write(fd, str + start_idx, end_idx - start_idx);
}

static void	mini_heredoc(t_envlst *env_list, char *file_name, char *last_str)
{
	int		fd;
	char	*input;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	signal(SIGINT, sighandler_heredoc);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			ft_putstr_fd("\033[1A\033[2C", STDOUT_FILENO);
		if (input == NULL || (ft_strlen(input) == ft_strlen(last_str)
				&& ft_strncmp(input, last_str, ft_strlen(input)) == 0))
		{
			close(fd);
			return ;
		}
		process_heredoc_env(env_list, fd, input);
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	free(input);
}

void	execute_heredoc(t_info *info, t_cmd *cmd_list)
{
	t_redir		*cur;
	int			cnt;
	char		*file_cnt;
	char		*file_name;

	cnt = 0;
	while (cmd_list)
	{
		cur = cmd_list->redir;
		while (cur)
		{
			if (ft_strncmp(cur->type, "<<", 2) == 0)
			{
				file_cnt = ft_itoa(cnt);
				file_name = ft_strjoin(file_cnt, ".tmp");
				mini_heredoc(info->env_list, file_name, cur->file);
				free_all_str(file_cnt, file_name, NULL, NULL);
			}
			cur = cur->next;
		}
		cnt++;
		cmd_list = cmd_list->next;
	}
	exit(0);
}

void	unlink_heredoc_files(t_cmd *cmd_list)
{
	int		cnt;
	char	*file_cnt;
	char	*file_name;

	cnt = 0;
	while (cmd_list)
	{
		file_cnt = ft_itoa(cnt);
		file_name = ft_strjoin(file_cnt, ".tmp");
		unlink(file_name);
		free_all_str(file_cnt, file_name, NULL, NULL);
		cmd_list = cmd_list->next;
		cnt++;
	}
}
