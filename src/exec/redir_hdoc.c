/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:43:52 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/28 14:17:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redir_check(t_minishell *ms)
{
	int			i;
	t_cmdlist	*tmp;
	int			size;

	i = 0;
	tmp = ms->cmdlist;
	size = ms->cmd_count;
	while (i < size - 1)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp->content->append || tmp->content->output || tmp->content->input
		|| tmp->content->heredoc)
		return (1);
	return (0);
}

//This function is supposed to check for >,<,>>,<< in main_array starting form
//	pos, until it reaches a pipe
//For example for the str= ls -l > file | wc -l < file;
//I call this function with pos = 0 to deal with all the redirects before the
//	1st pipe;
//Then I would call the function again with pos = 6 beacause thats where the
//	next command starts;
int	redir_in_out(t_content *content, char **arr, int pos)
{
	int			size;
	t_content	*tmp;

	tmp = content;
	size = arr_size(arr);
	while (pos < size && ft_strcmp(arr[pos], "|") != 0 )
	{
		if (tmp->input && ft_strcmp(arr[pos], "<") == 0)
			open_file_in(tmp, tmp->input);
		if (tmp->heredoc && ft_strcmp(arr[pos], "<<") == 0)
			open_file_hdoc(tmp, tmp->heredoc);
		if (tmp->output && ft_strcmp(arr[pos], ">") == 0)
			open_file_out(tmp, tmp->output);
		if (tmp->append && ft_strcmp(arr[pos], ">>") == 0)
			open_file_app(tmp, tmp->append);
		pos++;
	}
	return (0);
}

int	no_pipe(t_minishell *ms, char **paths, char **envp, char **arr)
{
	t_cmdlist	*tmp;
	pid_t		child;
	
	(void)arr;
	tmp = ms->cmdlist;
	child = fork();
	if (child == 0)
	{
		//redir_in_out(tmp->content, ms->main_arr, 0);
		exec(tmp, paths, envp);
	}
	else
	{
		wait(NULL);
		dup2(ms->fdout_buf, STDOUT_FILENO);
		close(ms->fdout_buf);
		dup2(ms->fdin_buf, STDIN_FILENO);
		close(ms->fdin_buf);
	}
	return (0);
}

int	ft_pipe(t_minishell *ms, t_cmdlist *cmdlist, int *pipe_fd, char **envp, char **paths, int j)
{
	pid_t		child;
	
	if (pipe(pipe_fd) < 0)
	{
		printf("Pipe error\n");
		return (1);
	}
	child = fork();
	if (child == -1)
		return (printf("Fork Error\n"));
	if (child == 0)
	{
		if (redir_check(ms))
		{
			redir_in_out(cmdlist->content, ms->main_arr, j);
		}
		else
		{	
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		exec(cmdlist, paths, envp);
	}
	else
	{
		close(pipe_fd[1]);
		wait (NULL);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	return (1);
}

int	run(t_minishell *ms, char **envp)
{
	int			i;
	int			j;
	int			cmds;
	t_cmdlist	*tmp;
	char		**paths;
	int			pipe_fd[2];

	i = 0;
	j = 0;
	tmp = ms->cmdlist;
	paths = path_init(envp);
	cmds = ms->cmd_count;
	if (cmds == 1) //if there isn't a pipe
	{
		redir_in_out(tmp->content, ms->main_arr, 0);
		no_pipe(ms, paths, envp, ms->main_arr);
		free_array(paths);
		return (1);
	}
	while (cmds > 1 && i < cmds) //if there's a pipe
	{
		ft_pipe(ms, tmp, pipe_fd, envp, paths, j);
		while (ms->main_arr[j] && ft_strcmp(ms->main_arr[j], "|") != 0)
			j++;
		if (tmp->next)
			tmp = tmp->next;
		j++;
		i++;
	}
	if (tmp && !redir_check(ms))
		exec(tmp, paths, envp);
	dup2(ms->fdout_buf, STDOUT_FILENO);
	close(ms->fdout_buf);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
	free_array(paths);
	return (0);
}
