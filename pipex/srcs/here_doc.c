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
	reader[0] = '\0';
	tmp = malloc(0);
	while (reader)
	{
		free(reader);
		reader = get_next_line(0);
		if (!ft_strncmp(reader, argv, ft_strlen(argv)))
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

void	parent_here_doc(int pipe_data[2], char **argv, char **env)
{
	char	**cmd;
	char	*path;
	int		file;

	cmd = NULL;
	path = NULL;
	file = open(argv[5], O_WRONLY | O_APPEND | O_CREAT);
	if (file == -1)
		error_message();
	cmd = ft_split(argv[4], ' ');
	if (!cmd)
		(error_message());
	path = path_for_execve(env, cmd[0]);
	if (!path || dup2(pipe_data[0], 0) == -1 || dup2(file, 1) == -1
		|| close(pipe_data[1]))
		(error_message());
	if (execve(path, cmd, env) == -1)
		(error_message());
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
		return (child_here_doc(pipe_data, argv));
	pid = wait(&status);
	if (pid == -1)
		error_message();
	if (status != 0)
		return (1);
	parent_here_doc(pipe_data, argv, env);
	return (0);
}
