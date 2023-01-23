/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:16:29 by marvin            #+#    #+#             */
/*   Updated: 2023/01/19 15:16:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(int file, char **argv, char **env, int pipe_data[2])
{
	char	**cmd;
	char	*path;

	cmd = NULL;
	path = NULL;
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		(free_all(pipe_data, file, NULL, NULL), error_message());
	path = path_for_execve(env, cmd[0]);
	if (!path || dup2(pipe_data[1], 1) == -1 || dup2(file, 0) == -1
		|| close(pipe_data[0]) == -1)
		(free_all(pipe_data, file, cmd, NULL), error_message());
	if (execve(path, cmd, env) == -1)
		(free_all(pipe_data, file, cmd, path), error_message());
}

void	last_child(int file, char **argv, char **env, int pipe_data[2])
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = NULL;
	path = NULL;
	i = 0;
	while (argv[i])
		i++;
	cmd = ft_split(argv[i - 2], ' ');
	if (!cmd)
		(free_all(pipe_data, file, NULL, NULL), error_message());
	path = path_for_execve(env, cmd[0]);
	if (!path || dup2(pipe_data[0], 0) == -1 || dup2(file, 1) == -1)
		(free_all(pipe_data, file, cmd, NULL), error_message());
	if (execve(path, cmd, env) == -1)
		(free_all(pipe_data, file, cmd, path), error_message());
}

void	execute_fork(int argc, char **argv, char **env, int pipe_data[2])
{
	pid_t		pid;
	static int	call = 0;
	int			file;

	if (call == 0)
		file = open(argv[1], O_RDONLY);
	else
		file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		(free_all(pipe_data, -1, NULL, NULL), error_message());
	pid = fork();
	if (pid == -1)
		(free_all(pipe_data, file, NULL, NULL), error_message());
	if (pid == 0)
	{
		if (call == 0)
			return (child(file, argv, env, pipe_data));
		else
			return (last_child(file, argv, env, pipe_data));
	}
	call++;
	if (waitpid(pid, NULL, 0) == -1)
		(free_all(pipe_data, file, NULL, NULL), error_message());
	close(file);
}

int	main(int argc, char **argv, char **env)
{
	int		pipe_data[2];

	if (argc < 5)
		return (ft_putstr_fd("Bad arguments\n", 2), 1);
	if (!ft_strncmp("here_doc", argv[1], 8)
		&& ft_strlen(argv[1]) == 8 && argc == 6)
		return (here_doc(argv, env));
	if (pipe(pipe_data) == -1)
		error_message();
	execute_fork(argc, argv, env, pipe_data);
	if (close(pipe_data[1]) == -1)
		(close(pipe_data[0]), error_message());
	many_pipes(argc, argv, env, &pipe_data[0]);
	execute_fork(argc, argv, env, pipe_data);
	if (close(pipe_data[0]) == -1)
		error_message();
}
