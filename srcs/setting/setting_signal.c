/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:10:16 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 17:20:24 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sighandler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putendl_fd("", STDOUT_FILENO);
		exit(1);
	}
}

void	sighandler_quit(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
	}
	exit(1);
}

void	sighandler_default(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("⊹ﾟ\033[36m✦𓂋 minishell𓂋 ✦\033[0mﾟ⊹$ ", STDERR_FILENO);
		g_termination_status = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setting_signal(void)
{
	signal(SIGINT, sighandler_default);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
