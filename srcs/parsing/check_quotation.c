/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:15:59 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 18:47:34 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	insert_tokens(t_token *tokens, char **res)
{
	t_token	*tmp;
	t_token	*tail;

	tail = tokens->next;
	tokens->next = NULL;
	free(tokens->str);
	tokens->str = ft_strdup(res[0]);
	add_token(&tokens, res[1], ARGV);
	add_token(&tokens, res[2], WORD);
	tmp = tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tail;
	free_all(res);
}

void	check_quotation(t_info *info, t_token *tokens)
{
	char	**str;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			str = split_quotation(info, tokens->str);
			if (str)
				insert_tokens(tokens, str);
		}
		tokens = tokens->next;
	}
}
