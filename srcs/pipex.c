/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:14:30 by taretiuk          #+#    #+#             */
/*   Updated: 2024/05/11 19:41:02 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("input file:");
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
		perror("Error file");
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

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc != 5)
	{
		ft_putendl_fd("Error: Wrong number arguments", 2);
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
