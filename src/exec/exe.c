/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:22:20 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/21 15:09:53 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**path_init(char **envp)
{
	int		i;
	char	**paths;
	char	**path_dir;
	char	*env_path;

	while (ft_strnstr(*++envp, "PATH=", 5) == NULL)
		;
	env_path = ft_strtrim(*envp, "PATH=");
	paths = ft_split(env_path, ':');
	path_dir = malloc(sizeof(char *) * (arr_size(paths) + 1));
	i = 0;
	while (i < arr_size(paths))
	{
		path_dir[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	path_dir[i] = NULL;
	free(env_path);
	free_array(paths);
	return (path_dir);
}

char	*is_exec(char *str, char **paths)
{
	int		i;
	char	*buf;
	
	i = 0;
	while (paths[i])
	{
		buf = ft_strjoin(paths[i], str);
		if (!access(buf, F_OK))
			return (buf);
		free(buf);
		i++;
	}
	return (NULL);
}

int	is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 ||
		ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0 ||
		ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 ||
		ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	built_ins(char *builtin)
{
	if (ft_strcmp(builtin, "echo") == 0)
		/* echo() */;
	if (ft_strcmp(builtin, "cd") == 0)
		/* cd() */;
	if (ft_strcmp(builtin, "pwd") == 0)
		pwd();
	if (ft_strcmp(builtin, "export") == 0)
		/* export() */;
	if (ft_strcmp(builtin, "unset") == 0)
		/* unset */;
	if (ft_strcmp(builtin, "env") == 0)
		/* env() */;
	if (ft_strcmp(builtin, "exit") == 0)
		/* exit() */;
}

int	childs(char **cmd_flags, char **envp, char *cmd_path)
{
	if (is_built_in(cmd_flags[0]))
	{
		built_ins(cmd_flags[0]);
		return (0);
	}
	if (cmd_path && execve(cmd_path, cmd_flags, envp) == -1)
		return (printf("EXECVE ERROR\n"));
	return (0);
}

int	exec(int fd_buf, char **cmd_flags, char **paths, char **envp)
{
	pid_t		child;
	char		*cmd_path;

	cmd_path = NULL;
	if (!is_built_in(cmd_flags[0]))
		cmd_path = is_exec(cmd_flags[0], paths);
	if (cmd_path || is_built_in(cmd_flags[0])) 
	{
		child = fork();
		if (child == -1)
			return(printf("Fork Error\n"));
		if (child == 0)
			childs(cmd_flags, envp, cmd_path);
		else
		{
			wait(NULL);
			dup2(fd_buf, STDOUT_FILENO);
			close(fd_buf);
		}
	}
	free(cmd_path);
	return (0);
}
