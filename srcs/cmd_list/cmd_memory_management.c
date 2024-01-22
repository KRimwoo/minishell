/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_memory_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:53:31 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/01/22 17:56:50 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_redirection_memory(t_redir *redirection_list)
{
	t_redir	*tmp;

	while (redirection_list)
	{
		if (redirection_list->type)
			free(redirection_list->type);
		if (redirection_list->file)
			free(redirection_list->file);
		tmp = redirection_list;
		redirection_list = redirection_list->next;
		free(tmp);
	}
}

void	free_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*tmp;

	while (*cmd_list)
	{
		tmp = (*cmd_list)->next;
		free_all((*cmd_list)->argv);
		free_redirection_memory((*cmd_list)->redir);
		free(*cmd_list);
		*cmd_list = tmp;
	}
}
