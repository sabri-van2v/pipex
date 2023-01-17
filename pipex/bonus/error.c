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