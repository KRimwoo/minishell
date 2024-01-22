/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:46:32 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/22 16:58:12 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envlst	*new_envlst(char *key, char *value)
{
	t_envlst	*new;

	new = (t_envlst *)malloc(sizeof(t_envlst));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_envlst(t_envlst **head, t_envlst *new)
{
	t_envlst	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_envlst	*create_env_node(char *envp)
{
	int		loc;
	char	*key;
	char	*value;

	loc = 0;
	while (envp[loc] && envp[loc] != '=')
		loc++;
	key = ft_substr(envp, 0, loc);
	if (envp[loc] != '\0')
		value = ft_substr(envp, loc + 1, ft_strlen(envp) - loc - 1);
	else
		value = NULL;
	return (new_envlst(key, value));
}

void	init_envlst(t_envlst **head, char *envp[])
{
	*head = NULL;
	while (*envp != NULL && **envp != '\0')
	{
		add_envlst(head, create_env_node(*envp));
		envp++;
	}
	return ;
}

void	get_path_list(t_info **info)
{
	t_envlst	*tmp;

	(*info)->path_list = NULL;
	tmp = (*info)->env_list;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->key, "PATH", 5))
			break ;
		tmp = tmp->next;
	}
	if (!((*info)->env_list))
		return ;
	(*info)->path_list = ft_split(tmp->value, ':');
}
