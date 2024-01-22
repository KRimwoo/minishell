/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:48:07 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 18:38:52 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *str, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(str);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **token, char *str, int type)
{
	t_token	*new;
	t_token	*tmp;

	new = new_token(str, type);
	if (!new)
		return ;
	if (!*token)
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*delete_token(t_token **head, t_token *target)
{
	t_token	*prev;
	t_token	*cur;

	if (target == *head)
	{
		free(target->str);
		target = target->next;
		free(*head);
		*head = target;
		return (target);
	}
	cur = *head;
	while (cur != target)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = cur->next;
	free(cur->str);
	free(cur);
	return (prev->next);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}
