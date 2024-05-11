/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:55:52 by taretiuk          #+#    #+#             */
/*   Updated: 2024/05/11 19:23:31 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_2d_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	check_cmd(char **cmd)
{
	if (cmd == 0 || *cmd == 0)
	{
		write(2, "permission denied:\n", 19);
		free(cmd);
		exit(-1);
	}
}

void	check_path(char **cmd, char *path)
{
	if (path == NULL)
	{
		write(2, "command not found\n", 18);
		free_2d_array(cmd);
		free(path);
		exit(-1);
	}
}

void	error_execve(char **cmd, char *path)
{
	free_2d_array(cmd);
	free(path);
	perror("Error execve");
	exit(-1);
}
