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

void	child(char **env, int pipe_data[2], t_exec p1)
{
	if (dup2(pipe_data[1], 1) == -1 || dup2(p1.file, 0) == -1)
		(free_all(pipe_data, p1), error_message());
	if (execve(p1.path, p1.cmd, env) == -1)
		(free_all(pipe_data, p1), error_message());
}

void	last_child(char **env, int pipe_data[2], t_exec p2)
{
	if (dup2(pipe_data[0], 0) == -1 || dup2(p2.file, 1) == -1)
		(free_all(pipe_data, p2), error_message());
	if (execve(p2.path, p2.cmd, env) == -1)
		(free_all(pipe_data, p2), error_message());
}

void	execute_child(char **argv, char **env, int pipe_data[2])
{
	pid_t		pid;
	t_exec		p1;

	p1.cmd = NULL;
	p1.path = NULL;
	p1.cmd = ft_split(argv[2], ' ');
	if (!p1.cmd)
		error_message();
	p1.path = path_for_execve(env, p1.cmd[0]);
	if (!p1.path)
		(free(p1.cmd), error_message());
	p1.file = open(argv[1], O_RDONLY);
	if (p1.file == -1)
		(free(p1.cmd), free(p1.path), error_message());
	pid = fork();
	if (pid == -1)
		error_message();
	if (pid == 0)
		child(env, pipe_data, p1);
	if (waitpid(pid, NULL, 1) == -1)
		error_message();
	free(p1.cmd);
	free(p1.path);
}

void	execute_last_child(int argc, char **argv, char **env, int pipe_data[2])
{
	pid_t		pid;
	t_exec		p2;

	p2.cmd = NULL;
	p2.path = NULL;
	p2.cmd = ft_split(argv[argc - 2], ' ');
	if (!p2.cmd)
		error_message();
	p2.path = path_for_execve(env, p2.cmd[0]);
	if (!p2.path)
		(free(p2.cmd), error_message());
	p2.file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
	if (p2.file == -1)
		(free(p2.cmd), free(p2.path), error_message());
	pid = fork();
	if (pid == -1)
		error_message();
	if (pid == 0)
		last_child(env, pipe_data, p2);
	if (waitpid(pid, NULL, 1) == -1)
		error_message();
	free(p2.cmd);
	free(p2.path);
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
	execute_child(argv, env, pipe_data);
	if (close(pipe_data[1]) == -1)
		(close(pipe_data[0]), error_message());
	if (argc > 5)
		many_pipes(argc, argv, env, &pipe_data[0]);
	execute_last_child(argc, argv, env, pipe_data);
	if (close(pipe_data[0]) == -1)
		error_message();
	return (0);
}
