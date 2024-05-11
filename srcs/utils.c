/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:12:36 by taretiuk          #+#    #+#             */
/*   Updated: 2024/05/11 19:40:25 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}
