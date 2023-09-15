/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:22:20 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/15 11:28:27 by ddiniz-m         ###   ########.fr       */
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

void	built_ins(char *builtin)
{
	if (!ft_strcmp(builtin, "echo"))
		/* echo() */;
	if (!ft_strcmp(builtin, "cd"))
		/* cd() */;
	if (!ft_strcmp(builtin, "pwd"))
		pwd();
	if (!ft_strcmp(builtin, "export"))
		/* export() */;
	if (!ft_strcmp(builtin, "unset"))
		/* unset */;
	if (!ft_strcmp(builtin, "env"))
		/* env() */;
	if (!ft_strcmp(builtin, "exit"))
		/* exit() */;
}

void	exec(char **cmd_flags, char **paths, char **env)
{
	char		*cmd_path;

	cmd_path = is_exec(cmd_flags[0], paths);
	if (!ft_strcmp(cmd_flags[0], "echo"))
	{
		built_ins(cmd_flags[0]);
	}
	else if (cmd_path && execve(cmd_path, cmd_flags, env) == -1)
		free(cmd_path);
	free(cmd_path);
}

int	run_cmds(t_minishell *ms, char **env)
{
	int			i;
	t_cmdlist	*cmds;
	char		**paths;
	
	i = 0;
	cmds = ms->cmdlist;
	paths = path_init(env);
	while (i < cmd_count(ms->main_arr))
	{
		exec(cmds->content->cmd_flags, paths, env);
		cmds = cmds->next;
		i++;
	}
	free_array(paths);
	return (1);
}