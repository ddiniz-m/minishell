/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:43:52 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/25 17:58:15 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redir_in(t_content *content, char **arr)
{
	int			size;
	t_content	*tmp;

	tmp = content;
	size = arr_size(arr) - 1;
	while (size > 0)
	{
		if (tmp->input && ft_strcmp(arr[size], "<") == 0)
		{
			content->fd_in = open(tmp->input->data, O_RDONLY);
			if (content->fd_in < 0)
				return (printf("OPEN ERROR\n"));
			dup2(content->fd_in, STDIN_FILENO);
			close(content->fd_in);
			break ;
		}
		if (tmp->heredoc && ft_strcmp(arr[size], "<<") == 0)
		{
			content->fd_in = open(tmp->heredoc->data, O_RDONLY);
			dup2(content->fd_in, STDIN_FILENO);
			close(content->fd_in);
			break ;
		}
		size--;
	}
	return (0);
}

int	redir_out(t_content *content, char **arr)
{
	int			size;
	t_content	*tmp;

	tmp = content;
	size = arr_size(arr) - 1;
	while (size > 0)
	{
		if (tmp->output && ft_strcmp(arr[size], ">") == 0)
		{
			content->fd_out = open(tmp->output->data, 
					O_CREAT | O_RDWR | O_TRUNC, 0777);
			dup2(content->fd_out, STDOUT_FILENO);
			close(content->fd_out);
			break ;
		}
		if (tmp->append && ft_strcmp(arr[size], ">>") == 0)
		{
			content->fd_out = open(tmp->append->data, 
					O_CREAT | O_RDWR | O_APPEND, 0777);
			dup2(content->fd_out, STDOUT_FILENO);
			close(content->fd_out);
			break ;
		}
		size--;
	}
	return (0);
}

int		close_parent(t_minishell *ms)
{
	wait(NULL);
	dup2(ms->fdout_buf, STDOUT_FILENO);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
	close(ms->fdout_buf);
	return (0);
}

int	no_pipe(t_cmdlist *tmp, char **paths, char **envp, char **arr)
{
	pid_t		child;

	child = fork();
	redir_in(tmp->content, arr);
	redir_out(tmp->content, arr);
	if (child == 0)
		exec(tmp, paths, envp);
	else
		wait(NULL);
	return (0);
}

int	run(t_minishell *ms, char **envp)
{
	int			i;
	int			cmds;
	t_cmdlist	*tmp;
	pid_t		child;
	char		**paths;
	int			pipe_fd[2];

	
	i = 1;
	tmp = ms->cmdlist;
	paths = path_init(envp);
	cmds = ms->cmd_count;
	if (cmds == 1) //if there isn't a pipe
	{
		no_pipe(tmp, paths, envp, ms->main_arr);
	}
	while (i <= cmds) //if there's a pipe
	{
		if (pipe(pipe_fd) < 0)
		{
			printf("Pipe error\n");
			break ;
		}
		child = fork();
		if (child == -1)
			return (printf("Fork Error\n"));
		if (child == 0)
		{
			if (i == 1) //first pipe
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				exec(tmp, paths, envp);
			}
			else if(i == cmds)// last pipe
			{
				close(pipe_fd[1]);
				wait (NULL);
				dup2(pipe_fd[0], STDIN_FILENO);
				close(pipe_fd[0]);
				exec(tmp, paths, envp);
			}
			else
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				dup2(pipe_fd[0], STDIN_FILENO);
				close(pipe_fd[0]);
				exec(tmp, paths, envp);
			}
		}
		else
		{
			wait(NULL);
			break ;
		}
		tmp = tmp->next;
		i++;
	}
	free_array(paths);
	close_parent(ms);
	return (0);
}
