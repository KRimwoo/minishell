/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:15:53 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 16:57:53 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_quotation(t_info *info, t_token *token, char *str, int loc)
{
	char	*rest;
	int		skip;

	skip = 1;
	while (str[loc + skip] && str[loc + skip] != str[loc])
		skip++;
	if (str[loc + skip] == '\0')
	{
		mini_error("quotation error\n", NULL);
		info->syntax_error = 1;
	}
	rest = ft_substr(str, loc + 1, skip - 1);
	if (rest && rest[0] != '\0')
		add_token(&token, rest, ARGV);
	free(rest);
	return (loc + skip + 1);
}

static int	get_argv_loc(t_info *info, t_token *token, char *str, int loc)
{
	int		skip;
	char	*tmp;

	while (str[loc] && !is_separator(str[loc]))
	{
		if (str[loc] == '\'' || str[loc] == '\"')
			loc = get_quotation(info, token, str, loc);
		else
		{
			skip = 1;
			while (str[loc + skip] && !is_separator(str[loc + skip])
				&& str[loc + skip] != '\'' && str[loc + skip] != '\"')
				skip++;
			tmp = ft_substr(str, loc, skip);
			if (tmp)
				add_token(&token, tmp, ARGV);
			free(tmp);
			loc += skip;
		}
	}
	return (loc);
}

static int	get_insertion_loc(char *str)
{
	int	start;
	int	skip;

	start = 0;
	while (str[start] && ft_strncmp(str + start, "<<", 2))
	{
		skip = 1;
		if (str[start] == '\'' || str[start] == '\"')
		{
			while (str[start + skip] && str[start + skip] != str[start])
				skip++;
			skip++;
		}
		start += skip;
	}
	return (start);
}

static void	parse_heredoc(t_info *info, t_token *token, char *str)
{
	int		loc;
	char	*new;

	if (!str)
		return ;
	loc = get_insertion_loc(str);
	if (str[loc] == '\0')
	{
		free(str);
		return ;
	}
	loc += 2;
	while (str[loc] && (str[loc] == ' '))
		loc++;
	free(token->str);
	token->str = ft_substr(str, 0, loc);
	loc = get_argv_loc(info, token, str, loc);
	new = ft_substr(str, loc, ft_strlen(str) - loc);
	add_token(&token, new, WORD);
	free(str);
	if (new)
		free(new);
}

void	check_heredoc(t_info *info, t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == WORD)
			parse_heredoc(info, tokens, ft_strdup(tokens->str));
		tokens = tokens->next;
	}
}
