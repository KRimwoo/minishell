/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:05:57 by yeeun             #+#    #+#             */
/*   Updated: 2024/01/22 12:23:22 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo_arguments(char **av, int idx)
{
	while (av[++idx])
	{
		if (av[idx][0] == '\0')
			continue ;
		ft_putstr_fd(av[idx], STDOUT_FILENO);
		if (av[idx + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
}

int	mini_echo(char **av)
{
	int	idx;
	int	n_idx;
	int	nextline;

	idx = 0;
	nextline = 1;
	if (av[1] && ft_strncmp(av[1], "-n", 2) == 0)
	{
		n_idx = 1;
		while (av[1][n_idx] == 'n')
			n_idx++;
		if (av[1][n_idx] == '\0')
			nextline = 0;
		if (av[1][n_idx] == '\0')
			idx++;
	}
	echo_arguments(av, idx);
	if (nextline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
