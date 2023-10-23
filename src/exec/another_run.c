/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:01:57 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/23 17:29:24 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	ft_putstr_fd("Minishell: error: Command not found.\n", STDERR_FILENO);
	g_exit = 1;
	return (NULL);
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
	paths = get_directories(ms->env);
	cmd_path = get_cmd_path(paths, cmd_arr[0]);
	free_array(paths);
	if (!cmd_path)
	{
		free(cmd_path);
		free(ms);
	}
	env = list_to_array(ms->env);
	execve(cmd_path, cmd_arr, env);
	free(cmd_path);
	g_exit = errno;
	free_ms(ms);
}

void	child(t_minishell *ms, t_cmdlist *cmd, int *pipe_fd, int pos)
{
	redirect(cmd->content, ms->main_arr, pos);
	if (!cmd->content->output && !cmd->content->append)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	exec(ms, cmd->content->cmd_flags);
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
	int		fd_in;
	pid_t	pid;

	tmp_cmd = ms->cmdlist;
	counter = ms->cmd_count;
	if (!tmp_cmd)
		return ;
	if (pipe(pipe_fd) < 0)
	{} // pipe error
	while (cmds_run < ms->cmd_count - 1)
	{
		pid = fork();
		if (pid < 0)
		{} // fork error
		if (pid == 0)
			child(ms, tmp_cmd, pipe_fd, pos);
		else
		{
			pos = find_cmd_pos(ms->main_arr, pos);
			tmp_cmd = tmp_cmd->next;
			cmds_run++;
			if (cmds_run > 1)
				close(fd_in);
			if (cmds_run < ms->cmd_count - 1)
			{
				close(pipe_fd[1]);
				fd_in = pipe_fd[0];
			}
			//dup2(pipe_fd[0], STDIN_FILENO);
		}
	}
	pid = fork();
	if (pid < 0)
	{} // fork error
	if (pid == 0)
	{
		redirect(tmp_cmd->content, ms->main_arr, pos);
		exec(ms, tmp_cmd->content->cmd_flags);
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
