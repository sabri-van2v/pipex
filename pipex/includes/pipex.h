/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:10:15 by svan-de-          #+#    #+#             */
/*   Updated: 2023/01/22 00:10:15 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>

void	free_split(char **split);

void	*free_path(char **paths, char *fill_path, char *final_path);

void	free_all(int pipe_data[2], int fd_file, char **cmd, char *path);

void	error_message(void);

char	*good_path(char **paths, char *fill_path, char *final_path, char *cmd);

char	*find_path(char	*env, char *cmd);

char	*path_for_execve(char **env, char *cmd);

void	check_access(char **argv);

void	child(char **argv, char **env, int pipe_data[2]);

void	parent(char **argv, char **env, int pipe_data[2]);

int		main(int argc, char **argv, char **env);

#endif