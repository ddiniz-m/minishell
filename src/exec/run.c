/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:01:57 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/24 17:08:34 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		while(buf[i])
			buf[i++] = 0;
	}
	if (cmd[0] == '/')
		paths[0] = ft_strjoin(NULL, "/");
	paths[1] = NULL;
	return (paths);
}

char	**get_directories(t_list **env)
{
	t_list	*tmp;
	char	**paths;
	char	**path_dir;
	int		i;

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
	g_exit = 1;
	if (strchr(cmd, '/'))
		perror(cmd);
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (NULL);
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
		{
			if (access(buf2, X_OK) == 0)
			{
				free(buf2);
				return (1);
			}
			perror("Minishell: error");
			g_exit = 1;
			free(buf2);
			return (free_array(paths));
		}
		free(buf2);
	}
	return (1);
}

void	exec(t_minishell *ms, char **cmd_arr)
{
	char	**paths;
	char	*cmd_path;
	char	**env;

	if (is_built_in(cmd_arr[0]))
	{
		built_ins(ms, cmd_arr, 0);
		free_ms(ms);
	}
	if (ft_strncmp(cmd_arr[0], "../", 3) == 0 || ft_strncmp(cmd_arr[0], "./", 2) == 0 \
		|| cmd_arr[0][0] == '/')
		paths = special_path(cmd_arr[0]);
	else
		paths = get_directories(ms->env);
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

int	find_cmd_pos(char **main_arr, int pos)
{
	while (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") !=\
		0)
		pos++;
	if (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") == 0)
		pos++;
	return (pos);
}

void	reset_fds(t_minishell *ms)
{
	dup2(ms->fdout_buf, STDOUT_FILENO);
	close(ms->fdout_buf);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
}

void	run(t_minishell *ms)
{
	t_cmdlist	*tmp_cmd;
	int		pipe_fd[2];
	int		counter;
	int		cmds_run = 0;
	int		pos = 0;
	int		status;
	int		fd_in = 0;
	pid_t	pid;

	tmp_cmd = ms->cmdlist;
	counter = ms->cmd_count;
	if (!tmp_cmd)
		return ;
	while (cmds_run < ms->cmd_count)
	{
		if (pipe(pipe_fd) < 0)
		{} // pipe error
		pid = fork();
		if (pid < 0)
		{} // fork error
		if (pid == 0)
		{
			if (cmds_run != 0) // Redirect input from the previous command or file
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (cmds_run < ms->cmd_count - 1) // Redirect output to the next command or file
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			if (ms->cmd_count == 1)
			{
				if (is_built_in(tmp_cmd->content->cmd_flags[0]))
					exit(g_exit);
			}
			redirect(tmp_cmd->content, ms->main_arr, pos);
			exec(ms, tmp_cmd->content->cmd_flags);
		}
		else
		{
			if (ms->cmd_count == 1)
			{
				if (is_built_in(tmp_cmd->content->cmd_flags[0]))
					built_ins(ms, tmp_cmd->content->cmd_flags, 0);
			}
			pos = find_cmd_pos(ms->main_arr, pos);
			tmp_cmd = tmp_cmd->next;
			if (cmds_run > 0)
				close(fd_in);
			if (cmds_run < ms->cmd_count - 1)
			{
				close(pipe_fd[1]);
				fd_in = pipe_fd[0];
			}
		}
		cmds_run++;
	}
	while (counter > 0)
	{
		wait(&status);
		if (pid != -1 && WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		counter--;
	}
	reset_fds(ms);
}
