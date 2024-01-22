/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:15:00 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:25:16 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	mini_change_longlong(char *str, long long *n)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str == '0')
		str++;
	if (sign == -1 && ft_strlen(str) == 19 \
	&& ft_strncmp(str, "9223372036854775808", 19) == 0)
	{
		*n = -9223372036854775807 - 1;
		return (1);
	}
	while (ft_isdigit(*str) && num * 10 + (*str - '0') >= num)
		num = num * 10 + (*str++ - '0');
	if (*str)
		return (0);
	*n = sign * num;
	return (1);
}

static void	set_exit_status(int arg_cnt, char *str)
{
	long long	exit_status;

	if (arg_cnt == 2)
	{
		if (mini_change_longlong(str, &exit_status))
			g_termination_status = (unsigned char)exit_status;
		else
		{
			ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
			ft_putstr_fd(str, STDOUT_FILENO);
			ft_putendl_fd(": numeric argument required", STDOUT_FILENO);
			g_termination_status = 255;
		}
	}
	else
		g_termination_status = 0;
}

int	mini_exit(t_info *info, t_cmd *cmd_list)
{
	int	arg_cnt;

	dup2(info->stdout, STDOUT_FILENO);
	if (cmd_list)
	{
		arg_cnt = 0;
		while (cmd_list->argv[arg_cnt])
			arg_cnt++;
		if (cmd_list->prev == NULL && cmd_list->next == NULL)
			ft_putendl_fd("exit", STDOUT_FILENO);
		if (arg_cnt > 2)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDOUT_FILENO);
			return (1);
		}
		set_exit_status(arg_cnt, cmd_list->argv[1]);
		unlink_heredoc_files(cmd_list);
		free_cmd_list(&cmd_list);
	}
	else
		ft_putendl_fd("exit", STDOUT_FILENO);
	free_all(info->path_list);
	exit(g_termination_status);
	return (0);
}
