/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:47:47 by taretiuk          #+#    #+#             */
/*   Updated: 2024/05/12 17:47:50 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	check_cmd(char **cmd)
{
	if (cmd == 0 || *cmd == 0)
	{
		write(2, "permission denied:\n", 19);
		free(cmd);
		exit(-1);
	}
}

static void	check_path(char **cmd, char *path)
{
	if (path == NULL)
	{
		write(2, "command not found\n", 18);
		free_2d_array(cmd);
		free(path);
		exit(-1);
	}
}

static void	error_execve(char **cmd, char *path)
{
	free_2d_array(cmd);
	free(path);
	perror("Error execve");
	exit(-1);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	check_cmd(cmd);
	path = find_path(cmd, envp);
	check_path(cmd, path);
	if (execve(path, cmd, envp) == -1)
		error_execve(cmd, path);
	free_2d_array(cmd);
	free(path);
}
