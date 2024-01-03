/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 13:46:31 by woorikim          #+#    #+#             */
/*   Updated: 2023/12/28 14:08:48 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	main(int argc, char **argv)
{
	if (argc != 5)
		print_error("Error: Wrong number of arguments");
		
}