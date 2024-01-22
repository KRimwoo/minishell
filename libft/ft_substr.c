/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:56:12 by woorikim          #+#    #+#             */
/*   Updated: 2023/03/22 20:07:57 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	size_t	i;
	char	*sbstr;

	sub_len = 0;
	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	while (*(s + start + sub_len) && sub_len < len)
		sub_len++;
	sbstr = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (!sbstr)
		return (0);
	while (i < sub_len)
	{
		*(sbstr + i) = *(s + start + i);
		i++;
	}
	*(sbstr + i) = '\0';
	return (sbstr);
}
