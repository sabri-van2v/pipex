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

void	free_split(char **split);

void	*free_path(char **paths, char *fill_path, char *final_path);

void	free_all(int pipe_data[2], int fd_file, char **cmd, char *path);

void	error_message(void);

void	pass(char *argv, char **env, int pipe_link[2], int pipe_data);

void	many_pipes(int argc, char **argv, char **env, int *pipe_data);

char	*get_doc(char *argv);

int		child_here_doc(int pipe_data[2], char **argv);

void	parent_here_doc(int pipe_data[2], char **argv, char **env);

int		here_doc(char **argv, char **env);

char	*good_path(char **paths, char *fill_path, char *final_path, char *cmd);

char	*find_path(char	*env, char *cmd);

char	*path_for_execve(char **env, char *cmd);

void	check_access(char **argv);

void	child(char **argv, char **env, int pipe_data[2]);

void	parent(int argx, char **argv, char **env, int pipe_data[2]);

int		main(int argc, char **argv, char **env);

#endif