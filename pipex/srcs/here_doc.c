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

#include "pipex.h"

char	*get_doc(char *argv)
{
	char	*reader;
	char	*str;
	char	*tmp;

	reader = malloc(1);
	tmp = malloc(1);
	if (!reader || !tmp)
		return (free(reader), free(tmp), NULL);
	reader[0] = '\0';
	tmp[0] = '\0';
	while (reader)
	{
		free(reader);
		reader = get_next_line(0);
		if (!ft_strncmp(reader, argv, ft_strlen(argv))
			&& ft_strlen(argv) + 1 == ft_strlen(reader))
			break ;
		str = ft_strjoin(tmp, reader);
		free(tmp);
		tmp = str;
	}
	free(reader);
	return (str);
}

int	child_here_doc(int pipe_data[2], char **argv)
{
	char	*str;

	str = get_doc(argv[2]);
	if (write(pipe_data[1], str, ft_strlen(str)) == -1)
		(free(str), error_message());
	free(str);
	return (0);
}

void	last_child_here_doc(int file, int pipe_data[2], char **argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = NULL;
	path = NULL;
	cmd = ft_split(argv[4], ' ');
	if (!cmd)
		(free_all(pipe_data, -1, NULL, NULL), error_message());
	path = path_for_execve(env, cmd[0]);
	if (!path || dup2(pipe_data[0], 0) == -1 || dup2(file, 1) == -1)
		(free_all(pipe_data, -1, cmd, NULL), error_message());
	if (execve(path, cmd, env) == -1)
		(free_all(pipe_data, -1, cmd, path), error_message());
}

int	here_doc(char **argv, char **env)
{
	int		pipe_data[2];
	pid_t	pid;
	int		file;

	if (pipe(pipe_data) == -1)
		error_message();
	pid = fork();
	if (pid == -1)
		(free_all(pipe_data, -1, NULL, NULL), error_message());
	if (pid == 0)
		return (child_here_doc(pipe_data, argv));
	if (waitpid(pid, NULL, 1) == -1 || close(pipe_data[1]) == -1)
		(free_all(pipe_data, -1, NULL, NULL), error_message());
	file = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file == -1)
		(free_all(pipe_data, -1, NULL, NULL), error_message());
	pid = fork();
	if (pid == -1)
		(free_all(pipe_data, file, NULL, NULL), error_message());
	if (pid == 0)
		last_child_here_doc(file, pipe_data, argv, env);
	if (waitpid(pid, NULL, 0) == -1)
		(free_all(pipe_data, file, NULL, NULL), error_message());
	free_all(pipe_data, file, NULL, NULL);
	return (0);
}
