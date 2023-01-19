/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:16:11 by marvin            #+#    #+#             */
/*   Updated: 2023/01/19 15:16:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_doc(char **argv)
{
	char	*reader;
	char	*str;

	reader = malloc(1);
	reader[0] = '\0';
	while (reader)
	{
		free(reader);
		reader = get_next_line(0);
		if (ft_strncmp(reader, argv[2], ft_strlen(argv[2])))
			break ;
		str = ft_strjoin(str, reader);
	}
	free(reader);
	return (str);
}

void	child_here_doc(int pipe_data[2], char **argv, char **env)
{
	char	*str;
	char	*path;
	char	**cmd;

	str = get_doc(argv);
	dup2(pipe_data[1], 1);
	write(0, str, ft_strlen(str));
	cmd = ft_split(argv[3], ' ');
	path = path_for_execve(env, cmd[0]);
	if (execve(path, cmd, env) == -1)
		error_message();
}

void	parent_here_doc(int pipe_data[2], char **argv, char **env)
{
	char	**cmd;
	char	*path;
	int		file;

	cmd = NULL;
	path = NULL;
	file = open(argv[5], O_WRONLY | O_APPEND | O_CREAT | O_TRUNC);
	if (file == -1)
			error_message();
	cmd = ft_split(argv[4], ' ');
	if (!cmd)
		(free_all(pipe_data, file, NULL, NULL), error_message());
	path = path_for_execve(env, cmd[0]);
	if (!path || dup2(pipe_data[0], 0) == -1 || dup2(file, 1) == -1 || close(pipe_data[1]) == -1)
		(free_all(pipe_data, file, cmd, NULL), error_message());
	if (execve(path, cmd, env) == -1)
		(free_all(pipe_data, file, cmd, path), error_message());
}

int	here_doc(char **argv, char **env)
{
	int		pipe_data[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_data) == -1)
		error_message();
	pid = fork();
	if (pid == 0)
		return (child_here_doc(pipe_data, argv, env), 0);
	pid = wait(&status);
	if (pid == -1)
		error_message();
	if (status != 0)
		return (1);
	parent_here_doc(pipe_data, argv, env);
	return (0);
}