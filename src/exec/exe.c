/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:22:20 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/22 16:27:00 by ddiniz-m         ###   ########.fr       */
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
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	built_ins(char *builtin)
{
	if (ft_strcmp(builtin, "echo") == 0)
		;/* echo() */
	if (ft_strcmp(builtin, "cd") == 0)
		;/* cd() */
	if (ft_strcmp(builtin, "pwd") == 0)
		pwd();
	if (ft_strcmp(builtin, "export") == 0)
		;/* export() */
	if (ft_strcmp(builtin, "unset") == 0)
		;/* unset */
	if (ft_strcmp(builtin, "env") == 0)
		;/* env() */
	if (ft_strcmp(builtin, "exit") == 0)
		;/* exit() */
}

int	child_process(t_content *content, char **envp, char *cmd_path)
{
	if (is_built_in(content->cmd_flags[0]))
	{
		built_ins(content->cmd_flags[0]);
		exit (0);
	}
	if (cmd_path && execve(cmd_path, content->cmd_flags, envp) == -1)
		perror("EXECVE ERROR\n");
	return (0);
}

int	exec(t_minishell *ms, t_cmdlist *cmdlist, char **paths, char **envp)
{
	pid_t		child;
	char		*cmd_path;

	cmd_path = NULL;
	if (!is_built_in(cmdlist->content->cmd_flags[0]))
		cmd_path = is_exec(cmdlist->content->cmd_flags[0], paths);
	if (cmd_path || is_built_in(cmdlist->content->cmd_flags[0])) 
	{
		child = fork();
		if (child == -1)
			return (printf("Fork Error\n"));
		if (child == 0)
			child_process(cmdlist->content, envp, cmd_path);
		else
		{
			free(cmd_path);
			return (child);
		}
	}
	free(cmd_path);
	return (0);
}
