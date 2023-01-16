#include "pipex.h"

void	error_message(void)
{
	perror("The program detected an error ");
	exit(1);
}

void	child(char **argv, char **env, int fds[2])
{
	char	**cmd;
	
	cmd = ft_split(argv[2], ' ');
	if (dup2(fds[0], 0) == -1 || close(fds[1]) == -1)
		error_message();
	
	if (execve(argv[1], cmd, env) == -1)
	{
		
		error_message();
		printf("555\n");
	}
	
}

void	parent(char **argv, char **env, int fds[2])
{
	char	**cmd;

	cmd = ft_split(argv[3], ' ');
	if (dup2(fds[1], 0) == -1 || close(fds[0]) == -1)
		error_message();
	if (execve(argv[4], cmd, env) == -1)
		error_message();
}

int	main(int argc, char **argv, char **env)
{
	int		fds[2];
	int		acc[2];
	pid_t	pid;
	int		status;

	if (argc == 5)
	{
		acc[0] = access(argv[1], R_OK);
		acc[1] = access(argv[4], F_OK);
		if (acc[1] != -1)
			acc[1] = access(argv[4], W_OK);
		if (acc[0] == -1 || acc[1] == -1)
			error_message();
		fds[0] = open(argv[1], O_RDONLY);
		fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
		if (fds[0] == -1 || fds[1] == -1)
			error_message();
		pid = fork();
		if (pid == -1)
			error_message();
		if (pid == 0)
			return (child(argv, env, fds), 0);
		
		pid = wait(&status);
		if (status != 0)
			return (1);
		parent(argv, env, fds);
	}
	else
		ft_putstr_fd("Bad arguments !\nEx : ./pipex file1 cmd1 cmd2 file2\n", 2);
}