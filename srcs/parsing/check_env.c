/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:15:37 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 18:47:03 by woorikim         ###   ########.fr       */
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
	if (res[1][0])
		add_token(&tokens, res[1], ARGV);
	if (res[3][0])
	{
		add_token(&tokens, res[2], SPACING);
		add_token(&tokens, res[3], ARGV);
	}
	add_token(&tokens, res[4], WORD);
	tmp = tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tail;
	free_all(res);
}

void	check_env(t_info *info, t_token *tokens)
{
	char	**str;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			str = split_env(info, tokens->str);
			if (str)
				insert_tokens(tokens, str);
		}
		tokens = tokens->next;
	}
}
