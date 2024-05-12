/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:45:29 by taretiuk          #+#    #+#             */
/*   Updated: 2024/05/12 17:46:15 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("input file");
		exit(-1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1 || 
		dup2(filein, STDIN_FILENO) == -1)
	{
		perror("Error dup2");
		exit(-1);
	}
	close(fd[0]);
	close(filein);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("ouput file");
		close(fileout);
		exit(-1);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1
		|| dup2(fileout, STDOUT_FILENO) == -1)
	{
		perror("Error dup2");
		exit(-1);
	}
	close(fd[1]);
	close(fileout);
	execute(argv[3], envp);
}
