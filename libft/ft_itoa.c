/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:13:36 by woorikim          #+#    #+#             */
/*   Updated: 2024/01/05 13:12:55 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nbrcpy(char *nbr, int i, size_t nbrlen)
{
	nbr[nbrlen] = '\0';
	if (i < 0)
	{
		nbr[0] = '-';
		i *= -1;
	}
	while (i != 0)
	{
		if (i > 0)
		{
			nbr[--nbrlen] = (i % 10) + '0';
		}
		else
		{
			nbr[--nbrlen] = -1 * (i % 10) + '0';
		}
		i /= 10;
	}
}

char	*ft_itoa(int i)
{
	int		tmp;
	char	*res;
	size_t	nbrlen;

	tmp = i;
	nbrlen = 0;
	if (i == 0)
		return (ft_strdup("0"));
	if (tmp < 0)
		nbrlen++;
	while (tmp != 0)
	{
		nbrlen++;
		tmp /= 10;
	}
	res = (char *)malloc(sizeof(char) * (nbrlen + 1));
	if (!res)
		return (0);
	ft_nbrcpy(res, i, nbrlen);
	return (res);
}
