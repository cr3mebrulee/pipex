/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:14:30 by taretiuk          #+#    #+#             */
/*   Updated: 2024/05/12 17:46:38 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc != 5)
	{
		ft_putendl_fd("Usage: infile cmd1 cmd2 outfile", 2);
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("Error pipe");
		exit(-1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Error fork");
		exit(-1);
	}
	if (pid1 == 0)
		child_process(argv, envp, fd);
	waitpid(-1, NULL, 0);
	parent_process(argv, envp, fd);
	return (0);
}
