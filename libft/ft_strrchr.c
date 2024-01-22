/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:33:15 by woorikim          #+#    #+#             */
/*   Updated: 2023/03/22 14:31:19 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*start_s;

	start_s = s;
	while (*s++)
		;
	while (--s >= start_s)
	{
		if (*s == (char)c)
			return ((char *)s);
	}
	return (0);
}
