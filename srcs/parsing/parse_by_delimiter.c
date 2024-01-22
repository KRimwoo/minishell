/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_by_delimiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:14:44 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 18:54:57 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**split_delimiter(char *str, char *delimiter)
{
	char	**res;
	int		start;
	int		end;

	start = 0;
	while (str[start]
		&& ft_strncmp(str + start, delimiter, ft_strlen(delimiter)))
		start++;
	if (str[start] == '\0')
		return (NULL);
	end = start + strlen(delimiter);
	res = malloc(sizeof(char *) * 4);
	if (!res)
		return (NULL);
	res[0] = ft_substr(str, 0, start);
	res[1] = ft_substr(str, start, end - start);
	res[2] = ft_substr(str, end, ft_strlen(str) - end);
	res[3] = NULL;
	return (res);
}

static void	insert_tokens(t_token *tokens, char **res, char *delimiter)
{
	t_token	*tmp;
	t_token	*tail;

	tail = tokens->next;
	tokens->next = NULL;
	free(tokens->str);
	tokens->str = ft_strdup(res[0]);
	if (delimiter[0] == ' ')
		add_token(&tokens, res[1], SPACING);
	else if (delimiter[0] == '|')
		add_token(&tokens, res[1], PIPE);
	else
		add_token(&tokens, res[1], REDIR);
	add_token(&tokens, res[2], WORD);
	tmp = tokens;
	while (tmp->next)
	tmp = tmp->next;
	tmp->next = tail;
	free_all(res);
}

void	check_delimeter(t_token *tokens, char *delimiter)
{
	char	**str;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			str = split_delimiter(tokens->str, delimiter);
			if (str)
				insert_tokens(tokens, str, delimiter);
		}
		tokens = tokens->next;
	}
}

void	parse_by_delimiter(t_token *tokens)
{
	check_delimeter(tokens, " ");
	check_delimeter(tokens, "|");
	check_delimeter(tokens, "<<");
	check_delimeter(tokens, ">>");
	check_delimeter(tokens, "<");
	check_delimeter(tokens, ">");
}
