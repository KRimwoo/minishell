/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:30:06 by woorikim          #+#    #+#             */
/*   Updated: 2023/03/25 16:20:13 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	add_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	add_len = 0;
	while (src[add_len] && (dest_len + add_len + 1 < dstsize))
	{
		dest[dest_len + add_len] = src[add_len];
		add_len++;
	}
	dest[dest_len + add_len] = '\0';
	if (dest_len < dstsize)
		return (dest_len + src_len);
	else
		return (dstsize + src_len);
}
