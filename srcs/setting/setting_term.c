/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:11:35 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 16:58:41 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	term_print_off(t_info *info)
{
	tcgetattr(STDIN_FILENO, &info->ms_termios);
	(&info->ms_termios)->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &info->ms_termios);
}

void	term_print_on(t_info *info)
{
	tcgetattr(STDIN_FILENO, &info->ms_termios);
	(&info->ms_termios)->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &info->ms_termios);
}
