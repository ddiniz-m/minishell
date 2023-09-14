/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:22:20 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/14 17:21:00 by ddiniz-m         ###   ########.fr       */
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

int	exec(t_minishell *ms, char **env)
{
	int			i;
	t_cmdlist	*cmds;
	char		**paths;
	char		*cmd_path;
	
	i = 0;
	cmds = ms->cmdlist;
	paths = path_init(env);
	while (i < cmd_count(ms->main_arr))
	{
		cmd_path = is_exec(cmds->content->cmd_flags[0], paths);
		if (cmd_path)
		{
			if (!is_builtin(cmds->content->cmd_flags[0]))
			{
				//call specific built-in func()
				printf("BUILT-IN!\n");
			}
			else if (execve(cmd_path, cmds->content->cmd_flags, env) == -1)
			{
				free(cmd_path);
				break ;
			}
			else
				printf("ERROR\n");
		}
		i++;
		cmds = cmds->next;
		free(cmd_path);
	}
	free_array(paths);
	return (1);
}