/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:43:52 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/11 12:49:42 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc(t_list *heredoc);

int	redir_check_out(t_content *content, char **arr, int pos)
{
	int			size;
	t_content	*tmp;

	tmp = content;
	size = arr_size(arr);
	while (pos < size && ft_strcmp(arr[pos], "|") != 0)
	{
		if (tmp->output && (ft_strcmp(arr[pos], ">") == 0
				|| ft_strcmp(arr[pos], ">>") == 0))
			return (1);
		pos++;
	}
	return (0);
}

int	redir_check_in(t_content *content, char **arr, int pos)
{
	int			size;
	t_content	*tmp;

	tmp = content;
	size = arr_size(arr);
	while (pos < size && ft_strcmp(arr[pos], "|") != 0)
	{
		if (tmp->input && (ft_strcmp(arr[pos], "<") == 0
				|| ft_strcmp(arr[pos], "<<") == 0))
			return (1);
		pos++;
	}
	return (0);
}

//These two functions are supposed to check for >,<,>>,<< in main_array
//	starting form pos, until it reaches a pipe
//For example for the str= ls -l > file | wc -l < file;
//I call this function with pos = 0 to deal with all the redirects before the
//	1st pipe;
//Then I would call the function again with pos = 6 beacause thats where the
//	next command starts;
int	redir_out(t_content *content, char **arr, int pos)
{
	int			size;
	t_content	*tmp;

	tmp = content;
	size = arr_size(arr);
	while (pos < size && ft_strcmp(arr[pos], "|") != 0)
	{
		if (tmp->output && ft_strcmp(arr[pos], ">") == 0)
			open_file_out(tmp, tmp->output);
		if (tmp->append && ft_strcmp(arr[pos], ">>") == 0)
			open_file_app(tmp, tmp->append);
		pos++;
	}
	return (0);
}

int	redir_in(t_content *content, char **arr, int pos)
{
	int			size;
	t_content	*tmp;
	t_list		*hdoc;

	tmp = content;
	hdoc = content->heredoc;
	size = arr_size(arr);
	while (pos < size && ft_strcmp(arr[pos], "|") != 0)
	{
		if (tmp->input && ft_strcmp(arr[pos], "<") == 0)
			open_file_in(tmp, tmp->input);
		if (hdoc && ft_strcmp(arr[pos], "<<") == 0)
		{
			while (hdoc)
			{
				heredoc(hdoc->data);
				hdoc = hdoc->next;
			}
		}
		pos++;
	}
	return (0);
}

void	set_fd(t_minishell *ms)
{
	dup2(ms->fdout_buf, STDOUT_FILENO);
	close(ms->fdout_buf);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
}
