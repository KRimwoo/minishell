/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_lexical.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:16:02 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 18:54:10 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	delete_empty(t_token **tokens)
{
	t_token	**head;
	t_token	*tmp;

	head = tokens;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (tmp->str[0] != '\0')
			{
				tmp->type = ARGV;
				tmp = tmp->next;
			}
			else
				tmp = delete_token(head, tmp);
		}
		else
			tmp = tmp->next;
	}
}

static void	delete_spacing(t_token **tokens)
{
	t_token	**head;
	t_token	*tmp;

	head = tokens;
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == SPACING)
		{
			tmp = delete_token(head, tmp);
			continue ;
		}
		tmp = tmp->next;
	}
}

static void	join_argvs(t_token **tokens)
{
	t_token	**head;
	t_token	*tmp;
	char	*new;

	head = tokens;
	tmp = *tokens;
	while (tmp && tmp->next)
	{
		if (tmp->type == ARGV && tmp->next->type == ARGV)
		{
			new = ft_strjoin(tmp->str, tmp->next->str);
			free(tmp->str);
			tmp->str = new;
			delete_token(head, tmp->next);
		}
		else
			tmp = tmp->next;
	}
}

t_token	*do_lexical(t_info *info, char *line)
{
	t_token	*tokens;

	tokens = new_token(line, WORD);
	check_heredoc(info, tokens);
	check_quotation(info, tokens);
	check_env(info, tokens);
	parse_by_delimiter(tokens);
	delete_empty(&tokens);
	join_argvs(&tokens);
	delete_spacing(&tokens);
	return (tokens);
}
