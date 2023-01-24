/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:03:57 by svan-de-          #+#    #+#             */
/*   Updated: 2023/01/22 19:03:57 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "get_next_line.h" 
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>

int		is_empty_string(char **argv);

void	free_split(char **split);

void	*free_path(char **paths, char *fill_path, char *final_path);

void	free_all(int pipe_data[2], int fd_file, char **cmd, char *path);

void	error_message(void);

void	pass(char *argv, char **env, int pipe_link[2], int pipe_data);

void	many_pipes(int argc, char **argv, char **env, int *pipe_data);

char	*get_doc(char *argv);

int		child_here_doc(int pipe_data[2], char **argv);

void	last_child_here_doc(int file, int pipe_data[2], char **argv,
			char **env);

int		here_doc(char **argv, char **env);

char	*good_path(char **paths, char *fill_path, char *final_path, char *cmd);

char	*find_path(char	*env, char *cmd);

char	*path_for_execve(char **env, char *cmd);

void	child(int file, char **argv, char **env, int pipe_data[2]);

void	last_child(int file, char **argv, char **env, int pipe_data[2]);

int		open_file(int argc, char **argv, int pipe_data[2], int flag);

void	execute_fork(int argc, char **argv, char **env, int pipe_data[2]);

int		main(int argc, char **argv, char **env);

#endif