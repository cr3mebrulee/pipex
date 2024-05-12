/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:02:46 by taretiuk          #+#    #+#             */
/*   Updated: 2024/05/12 13:03:28 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*return_path(char **paths, char **cmd)
{
	char	*part_path;
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd[0]);
		if (!part_path || !path)
		{
			free_2d_array(cmd);
			free(part_path);
			free(path);
			exit(-1);
		}
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char **cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	paths = NULL;
	path = NULL;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
	{
		free_2d_array(paths);
		free(path);
		free_2d_array(cmd);
		exit(-1);
	}
	path = return_path(paths, cmd);
	free_2d_array(paths);
	return (path);
}
