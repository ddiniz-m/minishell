/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:22:20 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/22 14:15:26 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**path_init(t_minishell *ms)
{
	int		i;
	char	**paths;
	char	*env_path;
	char	**path_dir;
	char	*env_path_str;

	env_path_str = var_str(*ms->env, "PATH=");
	env_path = ft_strtrim(env_path_str, "PATH=");
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

void	last_cmd(t_minishell *ms, t_cmdlist *cmdlist, int i)
{
	pid_t	child;
	int		status;

	if (cmdlist)
	{
		redirect(cmdlist->content, ms->main_arr, i);
		child = fork();
		if (child == 0)
			exec(ms, cmdlist);
		else
		{
			waitpid(child, &status, 0);
			if (WIFEXITED(status))
				g_exit = WEXITSTATUS(status);
			if (ft_strcmp(cmdlist->content->cmd_flags[0], "exit") == 0)
				exit_status(cmdlist->content->cmd_flags);
		}
	}
}
