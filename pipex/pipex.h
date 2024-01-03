/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 13:56:18 by woorikim          #+#    #+#             */
/*   Updated: 2023/12/28 14:18:04 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

# define FAIL 1
# define SUCCESS 0

typedef struct	s_cmd
{
	char	**cmd;
	char	*path;
}	t_cmd;

typedef struct s_info
{
	char	**envp;
	char	*infile;
	char	*outfile;
	int		pipe[2];
	int		fd_in;
	int		fd_out;
	int		pid;
	int		status;
}	t_info;
#endif