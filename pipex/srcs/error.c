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

void	free_all(int pipe_data[2], t_exec trash)
{
	int	set_errno;

	set_errno = errno;
	close(pipe_data[0]);
	close(pipe_data[1]);
	close(trash.file);
	if (trash.path)
		free(trash.path);
	free_split(trash.cmd);
	errno = set_errno;
}

void	error_message(void)
{
	perror("The program detected an error ");
	exit(1);
}
