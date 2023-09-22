/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:43:52 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/22 17:02:31 by ddiniz-m         ###   ########.fr       */
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

/* void	ft_pipe(t_minishell *ms, t_cmdlist *cmd)
{
	int	pipe_fd[2];
	
} */

void	run(t_minishell *ms, char **envp)
{
	t_cmdlist	*tmp;
	char		**paths;
	int			child_pid;
	int			pipe_fd[2];
	

	tmp = ms->cmdlist;
	paths = path_init(envp);
	while (tmp)
	{
		if (!tmp->next) //if there isn't a pipe
		{	
			redir_in(tmp->content, ms->main_arr);
			redir_out(tmp->content, ms->main_arr);
			child_pid = exec(ms, tmp, paths, envp);
		}
		else //if there's a pipe
		{
			/* ft_pipe(ms, tmp); */
			
			tmp = tmp->next;
			child_pid = exec(ms, tmp, paths, envp);
			continue ;
		}
		if (child_pid)
			break ;
		tmp = tmp->next;
	}
	wait(NULL);
	dup2(ms->fdout_buf, STDOUT_FILENO);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
	close(ms->fdout_buf);
	free_array(paths);	
}
