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

void	pass(char *argv, char **env, int pipe_link[2], int pipe_data)
{
	char	**cmd;
	char	*path;

	cmd = NULL;
	path = NULL;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		error_message();
	path = path_for_execve(env, cmd[0]);
	if (!path || dup2(pipe_data, 0) == -1 || dup2(pipe_link[1], 1) == -1)
		error_message();
	if (execve(path, cmd, env) == -1)
		error_message();
}

void	many_pipes(int argc, char **argv, char **env, int *pipe_data)
{
	pid_t	pid;
	int		i;
	int		pipe_link[2];

	i = 3;
	while (i < argc - 2)
	{
		if (pipe(pipe_link) == -1)
			error_message();
		pid = fork();
		if (pid == -1)
			error_message();
		if (pid == 0)
			pass(argv[i], env, pipe_link, *pipe_data);
		dup2(pipe_link[0], *pipe_data);
		close(pipe_link[1]);
		close(pipe_link[0]);
		i++;
	}
	waitpid(pid, NULL, 1);
}

