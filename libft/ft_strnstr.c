/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:18:04 by woorikim          #+#    #+#             */
/*   Updated: 2023/03/25 13:23:15 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hay_idx;
	size_t	need_idx;
	size_t	start;

	hay_idx = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (*(haystack + hay_idx) && (hay_idx < len))
	{
		need_idx = 0;
		if (*(haystack + hay_idx) == *(needle + need_idx))
		{
			start = hay_idx;
			while (*(haystack + start) == *(needle + need_idx)
				&& start < len && *(needle + need_idx))
			{
				start++;
				need_idx++;
			}
			if (!*(needle + need_idx))
				return ((char *)(haystack + hay_idx));
		}
		hay_idx++;
	}
	return (0);
}
