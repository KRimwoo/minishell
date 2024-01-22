/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:15:14 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 12:24:22 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_env(t_envlst *envlst)
{
	while (envlst)
	{
		if (envlst->value)
		{
			ft_putstr_fd(envlst->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(envlst->value, STDOUT_FILENO);
		}
		envlst = envlst->next;
	}
	return (0);
}
