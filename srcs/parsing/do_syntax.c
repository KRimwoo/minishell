/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:16:14 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 16:58:09 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_pipe(t_token *tokens)
{
	t_token	*prev;
	t_token	*cur;

	prev = NULL;
	cur = tokens;
	while (cur)
	{
		if (cur->type == PIPE)
		{
			if (!prev || !tokens->next || tokens->next->type == PIPE)
			{
				mini_error("unexpected token error: '|'\n", NULL);
				return (0);
			}
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}

static int	is_valid_redir(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIR)
		{
			if (!tokens->next || tokens->next->type != ARGV)
			{
				mini_error("unexpected token error: '>'\n", NULL);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

int	do_syntax(t_token *tokens)
{
	if (!is_valid_pipe(tokens) || !is_valid_redir(tokens))
		return (1);
	return (0);
}
