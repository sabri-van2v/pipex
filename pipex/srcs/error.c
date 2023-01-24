/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:16:44 by marvin            #+#    #+#             */
/*   Updated: 2023/01/19 15:16:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_empty_string(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		if (argv[i][0] == '\0')
			return (1);
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
			i++;
		i--;
		while (i >= 0)
		{
			free(split[i]);
			i--;
		}
		free(split);
	}
}

void	*free_path(char **paths, char *fill_path, char *final_path)
{
	if (fill_path)
		free(fill_path);
	if (final_path)
		free(final_path);
	free_split(paths);
	return (NULL);
}

void	free_all(int pipe_data[2], int fd_file, char **cmd, char *path)
{
	int	set_errno;

	set_errno = errno;
	close(pipe_data[0]);
	close(pipe_data[1]);
	close(fd_file);
	if (path)
		free(path);
	free_split(cmd);
	errno = set_errno;
}

void	error_message(void)
{
	perror("The program detected an error ");
	exit(1);
}
