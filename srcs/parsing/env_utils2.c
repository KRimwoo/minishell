/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:06:41 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 16:58:15 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_envval(t_envlst *head, char *key)
{
	char		*value;
	t_envlst	*tmp;

	tmp = head;
	while (tmp && (ft_strlen(key) != ft_strlen(tmp->key)
			|| ft_strncmp(key, tmp->key, ft_strlen(key))))
		tmp = tmp->next;
	if (tmp)
		value = ft_strdup(tmp->value);
	else
		value = ft_strdup("");
	free(key);
	return (value);
}

void	free_envlst(t_envlst *head)
{
	t_envlst	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
