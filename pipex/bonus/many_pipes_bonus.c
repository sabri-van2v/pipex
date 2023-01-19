/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:26 by marvin            #+#    #+#             */
/*   Updated: 2023/01/19 16:56:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pass(int i, char **argv, char **env, int pipe_data[2])
{
	char	**cmd;
	char	*path;

	cmd = NULL;
	path = NULL;
	cmd = ft_split(argv[i], ' ');
	path = path_for_execve(env, cmd[0]);
    dup2(pipe_data[0], 0);
    dup2(pipe_data[1], 1);
	if (!path || dup2(pipe_data[0], 0) == -1)
		(free_all(pipe_data, -1, cmd, NULL), error_message());
	if (execve(path, cmd, env) == -1)
		(free_all(pipe_data, -1, cmd, path), error_message());
}

void	many_pipes(int argc, char **argv, char **env, int pipe_data[2])
{
	pid_t	pid;
	pid_t	check_wait;
	int		status;
	int		i;

	i = 3;
	while (i < argc - 1)
	{
		pid = fork();
		if (pid == -1)
			error_message();
		if (pid == 0)
			pass(i, argv, env, pipe_data);
		check_wait = wait(&status);
		if (check_wait == -1)
			error_message();
		if (status != 0)
			exit (1);
        i++;
	}
}