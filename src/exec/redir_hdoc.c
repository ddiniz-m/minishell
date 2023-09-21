/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:43:52 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/21 14:50:30 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redir_in(t_content *content, char **arr)
{
	int			i;
	t_content	*tmp;

	i = 0;
	tmp = content;
	while (arr[i])
	{
		if(tmp->input && ft_strcmp(arr[i], "<") == 0)
		{
			content->fd_in = open(tmp->input->data, O_RDONLY);
			tmp->input = tmp->input->next;
			dup2(content->fd_in, STDIN_FILENO);
			close(content->fd_in);
		}
		if(tmp->input && ft_strcmp(arr[i], "<<") == 0)
		{
			content->fd_in = open(tmp->input->data, O_RDONLY);
			tmp->input = tmp->input->next;
			dup2(content->fd_in, STDIN_FILENO);
			close(content->fd_in);
		}
		i++;
	}
	return (0);
}

int	redir_out(t_content *content, char **arr)
{
	int			i;
	t_content	*tmp;

	i = 0;
	tmp = content;
	while (arr[i])
	{
		if(tmp->output && ft_strcmp(arr[i], ">") == 0)
		{
			content->fd_out = open(tmp->output->data, O_CREAT | O_RDWR | O_TRUNC, 0777);
			tmp->output = tmp->output->next;
			dup2(content->fd_out, STDOUT_FILENO);
			close(content->fd_out);
		}
		if(tmp->output && ft_strcmp(arr[i], ">>") == 0)
		{
			content->fd_out = open(tmp->output->data, O_CREAT | O_RDWR | O_APPEND, 0777);
			tmp->output = tmp->output->next;
			dup2(content->fd_out, STDOUT_FILENO);
			close(content->fd_out);
		}
		i++;
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
		exec(fd_buf, tmp->content->cmd_flags, paths, envp);
		tmp = tmp->next;
	}
	free_array(paths);
}