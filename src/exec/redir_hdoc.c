/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:43:52 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/22 14:50:32 by ddiniz-m         ###   ########.fr       */
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
		if(tmp->input && ft_strcmp(arr[size], "<") == 0)
		{
			content->fd_in = open(tmp->input->data, O_RDONLY);
			if (content->fd_in < 0)
				return (printf("OPEN ERROR\n"));
			dup2(content->fd_in, STDIN_FILENO);
			close(content->fd_in);
			break ;
		}
		if(tmp->heredoc && ft_strcmp(arr[size], "<<") == 0)
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
		if(tmp->output && ft_strcmp(arr[size], ">") == 0)
		{
			content->fd_out = open(tmp->output->data, O_CREAT | O_RDWR | O_TRUNC, 0777);
			dup2(content->fd_out, STDOUT_FILENO);
			close(content->fd_out);
			break ;
		}
		if(tmp->append && ft_strcmp(arr[size], ">>") == 0)
		{
			content->fd_out = open(tmp->append->data, O_CREAT | O_RDWR | O_APPEND, 0777);
			dup2(content->fd_out, STDOUT_FILENO);
			close(content->fd_out);
			break ;
		}
		size--;
	}
	return (0);
}

void	run(t_minishell *ms, char **envp)
{
	int			fd_buf;
	t_cmdlist	*tmp;
	char		**paths;

	fd_buf = dup(STDOUT_FILENO);
	tmp = ms->cmdlist;
	paths = path_init(envp);
	while (tmp)
	{
		redir_in(tmp->content, ms->main_arr);
		redir_out(tmp->content, ms->main_arr);
		exec(tmp, fd_buf, paths, envp);
		tmp = tmp->next;
	}
	free_array(paths);
}