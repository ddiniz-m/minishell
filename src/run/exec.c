/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:13:44 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/30 16:40:22 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec(t_minishell *ms, char **cmd_arr)
{
	char	**paths;
	char	*cmd_path;
	char	**env;

	if (!cmd_arr || !cmd_arr[0] || !cmd_arr[0][0])
		free_ms(ms);
	if (is_built_in(cmd_arr[0]))
	{
		built_ins(ms, cmd_arr);
		free_ms(ms);
	}
	paths = get_paths(ms->env, cmd_arr[0]);
	if (is_exec(cmd_arr[0], paths) == 0)
		free_ms(ms);
	cmd_path = get_cmd_path(paths, cmd_arr[0]);
	free_array(paths);
	if (!cmd_path)
		free_ms(ms);
	env = list_to_array(ms->env);
	execve(cmd_path, cmd_arr, env);
	free(cmd_path);
	g_exit = errno;
	free_ms(ms);
}

int	is_usable(char	*cmd, char *cmd_path, char **paths_array)
{
	struct stat path_stat;

	stat(cmd_path, &path_stat);
	if (S_ISDIR(path_stat.st_mode) != 0)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		g_exit = 126;
	}
	else if (access(cmd_path, X_OK) == 0)
	{
		free(cmd_path);
		return (1);
	}
	else
	{
		perror("Minishell: error: ");
		g_exit = 1;
	}
	free(cmd_path);
	free_array(paths_array);
	return (0);
}

int	is_exec(char *cmd, char **paths)
{
	int		i;
	char	*buf;
	char	*buf2;

	i = 0;
	while (paths[i])
	{
		buf = ft_strjoin(paths[i++], "/");
		buf2 = ft_strjoin(buf, cmd);
		free(buf);
		if (access(buf2, F_OK) == 0)
			return (is_usable(cmd, buf2, paths));
		free(buf2);
	}
	return (1);
}

char	**special_path(const char *cmd)
{
	char	**paths;
	char	buf[PATH_MAX + 1];
	int		i;

	i = 0;
	paths = malloc(sizeof(char *) * 2);
	if (ft_strncmp(cmd, "../", 3) == 0 || ft_strncmp(cmd, "./", 2) == 0)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			free(paths);
			return (NULL);
		}
		paths[0] = ft_strjoin(buf, "/");
		while (buf[i])
			buf[i++] = 0;
	}
	if (cmd[0] == '/')
		paths[0] = ft_strjoin(NULL, "/");
	paths[1] = NULL;
	return (paths);
}

char	**get_paths(t_list **env, char *cmd)
{
	t_list	*tmp;
	char	**paths;
	char	**path_dir;
	int		i;

	if (ft_strncmp(cmd, "../", 3) == 0 || ft_strncmp(cmd, "./", 2 ) == 0 \
		|| cmd[0] == '/')
		return (special_path(cmd));
	tmp = *env;
	while (tmp && strncmp(tmp->data, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp->data + 5, ':');
	path_dir = malloc(sizeof(char *) * (arr_size(paths) + 1));
	i = 0;
	while (i < arr_size(paths))
	{
		path_dir[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	path_dir[i] = NULL;
	free_array(paths);
	return (path_dir);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*buf1;
	char	*buf2;
	int		i;

	i = 0;
	while (paths[i])
	{
		buf1 = ft_strjoin(paths[i], "/");
		buf2 = ft_strjoin(buf1, cmd);
		free(buf1);
		if (access(buf2, 0) == 0)
			return (buf2);
		free(buf2);
		i++;
	}
	g_exit = 127;
	if (strchr(cmd, '/'))
		perror(cmd);
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (NULL);
}
