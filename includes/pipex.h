/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:14:15 by taretiuk          #+#    #+#             */
/*   Updated: 2024/05/11 19:27:40 by taretiuk         ###   ########.fr       */
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

void	parent_process(char **argv, char **envp, int *fd);
void	child_process(char **argv, char **envp, int *fd);
char	*find_path(char **cmd, char **envp);
char	*return_path(char **paths, char **cmd);
void	execute(char *argv, char **envp);
void	free_2d_array(char **array);
void	check_cmd(char **cmd);
void	check_path(char **cmd, char *path);
void	error_execve(char **cmd, char *path);
int		get_next_line(char **line);

#endif
