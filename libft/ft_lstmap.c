/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:11:17 by woorikim          #+#    #+#             */
/*   Updated: 2023/03/25 14:54:12 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*start;
	void	*lstcontent;

	start = NULL;
	while (lst)
	{
		lstcontent = f(lst->content);
		newlst = ft_lstnew(lstcontent);
		if (!newlst)
		{
			ft_lstclear(&start, del);
			del(lstcontent);
			return (0);
		}
		ft_lstadd_back(&start, newlst);
		lst = lst->next;
	}
	return (start);
}
