#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

void	error_message(void);

char	*good_path(char	*env, char *cmd);

char	*path_for_execve(char **env, char *cmd);

void	child(char **argv, char **env, int fds[2]);

void	parent(char **argv, char **env, int fds[2]);

int		main(int argc, char **argv, char **env);

#endif