/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:04:49 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 16:58:21 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	argv_len(t_token *tokens)
{
	int	len;

	len = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == ARGV)
			len++;
		else if (tokens->type == REDIR)
			len--;
		tokens = tokens->next;
	}
	return (len);
}

static char	**argv_list(t_token *tokens)
{
	char	**argv;
	int		index;

	argv = (char **)malloc(sizeof(char *) * (argv_len(tokens) + 1));
	if (!argv)
		return (NULL);
	index = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == ARGV)
			argv[index++] = ft_strdup(tokens->str);
		else if (tokens->type == REDIR)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	argv[index] = NULL;
	return (argv);
}

static	void	redir_list(t_cmd **cmds, t_token *tokens)
{
	t_redir	*redir;

	if ((*cmds)->redir == NULL)
	{
		(*cmds)->redir = new_redir(tokens);
	}
	else
	{
		redir = (*cmds)->redir;
		while (redir->next)
			redir = redir->next;
		redir->next = new_redir(tokens);
	}
}

t_cmd	*parse_cmds(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*head;

	cmds = new_cmd();
	head = cmds;
	while (tokens)
	{
		if (cmds->argv == NULL && tokens->type == ARGV)
			cmds->argv = argv_list(tokens);
		else if (tokens->type == REDIR)
		{
			redir_list(&cmds, tokens);
			tokens = tokens->next;
		}
		else if (tokens->type == PIPE)
		{
			cmds->next = new_cmd();
			cmds->next->prev = cmds;
			cmds = cmds->next;
		}
		tokens = tokens->next;
	}
	return (head);
}
