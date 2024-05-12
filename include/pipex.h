/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:14:15 by taretiuk          #+#    #+#             */
/*   Updated: 2024/05/12 12:55:28 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <errno.h>

void	free_2d_array(char **array);
//static	error_execve(char **cmd, char *path);
//static	check_path(char **cmd, char *path);
char	*return_path(char **paths, char **cmd);
char	*find_path(char **cmd, char **envp);
//static	check_cmd(char **cmd);
void	execute(char *argv, char **envp);
void	parent_process(char **argv, char **envp, int *fd);
void	child_process(char **argv, char **envp, int *fd);
//int		get_next_line(char **line);

#endif
