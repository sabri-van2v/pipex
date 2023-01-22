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

void	check_access(char **argv)
{
	int	acc[2];
	int	i;

	i = 0;
	while (argv[i])
		i++;
	i--;
	acc[0] = access(argv[1], R_OK);
	acc[1] = access(argv[i], W_OK);
	if (acc[0] == -1 || acc[1] == -1)
		error_message();
}

void	child(char **argv, char **env, int pipe_data[2])
{
	char	**cmd;
	char	*path;
	int		file;

	cmd = NULL;
	path = NULL;
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		error_message();
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

void	parent(int argc, char **argv, char **env, int pipe_data[2])
{
	char	**cmd;
	char	*path;
	int		file;

	cmd = NULL;
	path = NULL;
	file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
	if (file == -1)
		error_message();
	cmd = ft_split(argv[argc - 2], ' ');
	if (!cmd)
		(free_all(pipe_data, file, NULL, NULL), error_message());
	path = path_for_execve(env, cmd[0]);
	if (!path || dup2(pipe_data[0], 0) == -1 || dup2(file, 1) == -1)
		(free_all(pipe_data, file, cmd, NULL), error_message());
	if (execve(path, cmd, env) == -1)
		(free_all(pipe_data, file, cmd, path), error_message());
}

int	main(int argc, char **argv, char **env)
{
	int		pipe_data[2];
	pid_t	pid;
	int		status;

	if (argc < 5)
		return (ft_putstr_fd("Bad arguments\n", 2), 1);
	if (!ft_strncmp("here_doc", argv[1], 8)
		&& ft_strlen(argv[1]) == 8 && argc == 6)
		return (here_doc(argv, env));
	if (pipe(pipe_data) == -1)
		error_message();
	pid = fork();
	if (pid == -1)
		error_message();
	if (pid == 0)
		child(argv, env, pipe_data);
	pid = wait(&status);
	if (close(pipe_data[1]) || pid == -1)
		(close(pipe_data[0]), error_message());
	if (status != 0)
		return (1);
	many_pipes(argc, argv, env, &pipe_data[0]);
	parent(argc, argv, env, pipe_data);
}
