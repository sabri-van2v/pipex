#include "pipex.h"

void	check_access(char **argv)
{
	int	acc[2];

	acc[0] = access(argv[1], R_OK);
	acc[1] = access(argv[4], W_OK);
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
	if (dup2(pipe_data[1], 1) == -1 || dup2(file, 0) == -1 || close(pipe_data[0]) == -1)
		(free_all(pipe_data, file, cmd, NULL), error_message());
	path = path_for_execve(env, cmd[0]);
	if (!path)
		(free_all(pipe_data, file, cmd, NULL), error_message());
	if (execve(path, cmd, env) == -1)
		(free_all(pipe_data, file, cmd, path), error_message());
}

void	parent(char **argv, char **env, int pipe_data[2])
{
	char	**cmd;
	char	*path;
	int		file;

	cmd = NULL;
	path = NULL;
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (file == -1)
			error_message();
	cmd = ft_split(argv[3], ' ');
	if (!cmd)
		(free_all(pipe_data, file, NULL, NULL), error_message());
	if (dup2(pipe_data[0], 0) == -1 || dup2(file, 1) == -1 || close(pipe_data[1]) == -1)
		(free_all(pipe_data, file, cmd, NULL), error_message());
	path = path_for_execve(env, cmd[0]);
	if (!path)
		(free_all(pipe_data, file, cmd, NULL), error_message());
	if (execve(path, cmd, env) == -1)
		(free_all(pipe_data, file, cmd, path), error_message());
}

int	main(int argc, char **argv, char **env)
{
	int		pipe_data[2];
	pid_t	pid;
	int		status;

	if (argc == 5)
	{
		check_access(argv);
		if (pipe(pipe_data) == -1)
			error_message();
		pid = fork();
		if (pid == -1)
			error_message();
		if (pid == 0)
			return (child(argv, env, pipe_data), 0);
		pid = wait(&status);
		if (pid == -1)
			error_message();
		if (status != 0)
			return (1);
		parent(argv, env, pipe_data);
	}
	else
		ft_putstr_fd("Bad arguments !\n$./pipex file1 cmd1 cmd2 file2\n", 2);
}