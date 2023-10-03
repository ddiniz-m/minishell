/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:22:20 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/03 15:18:29 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**path_init(t_list **env)
{
	int		i;
	char	**paths;
	char	**path_dir;
	char	*env_path;
	t_list	*tmp;

	tmp = *env;
	while (ft_strnstr((char *)tmp->data, "PATH=", 5) == NULL)
		tmp = tmp->next;
	env_path = ft_strtrim((char *)tmp->data, "PATH=");
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

void	built_ins(t_minishell *ms, char *builtin)
{
	if (ft_strcmp(builtin, "echo") == 0)
		;/* echo() */
	if (ft_strcmp(builtin, "cd") == 0)
		;/* cd() */
	if (ft_strcmp(builtin, "pwd") == 0)
		pwd();
	if (ft_strcmp(builtin, "export") == 0)
	{
		list_sort(ms->exp);
		if (export_error(ms->main_arr))
			return ;
		if (arr_size(ms->main_arr) > 1)
			export(ms->main_arr, ms->exp, ms->env);
		else
			list_print(ms->exp);
	}
	if (ft_strcmp(builtin, "unset") == 0)
	{
		if (arr_size(ms->main_arr) > 1)
			unset(ms->env, ms->exp, ms->main_arr);
}
	if (ft_strcmp(builtin, "env") == 0)
		list_print(ms->env);
	if (ft_strcmp(builtin, "exit") == 0)
		;/* exit() */
}

int	last_cmd(t_minishell *ms, t_cmdlist *cmdlist)
{
	pid_t	child;

	if (cmdlist && !redir_check(ms))
	{
		child = fork();
		if (child == 0)
			exec(ms, cmdlist);
		else
			wait(NULL);
	}
	return (0);
}
