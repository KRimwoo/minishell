/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:10:09 by woorikim          #+#    #+#             */
/*   Updated: 2023/03/24 14:42:39 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	strnum[12];
	size_t	index;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = 0 - n;
	}
	index = 0;
	strnum[index] = n % 10 + '0';
	n /= 10;
	index++;
	while (n > 0)
	{
		strnum[index++] = n % 10 + '0';
		n /= 10;
	}
	while (index)
		ft_putchar_fd(strnum[(index--) - 1], fd);
}
