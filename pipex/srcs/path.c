#include "pipex.h"

char	*good_path(char	*env, char *cmd)
{
	char	**paths;
	char	*fill_path;
	char	*final_path;
	int		i;

	i = 0;
	paths = ft_split(&env[5], ':');
	while (paths[i])
	{
		fill_path = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(fill_path, cmd);
		if (!access(final_path, F_OK))
			return (final_path);
		i++;
	}
	return (NULL);
}

char	*path_for_execve(char **env, char *cmd)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
			return (good_path(env[i], cmd));
		i++;
	}
	return (NULL);
}
