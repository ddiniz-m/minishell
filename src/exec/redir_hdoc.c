/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:43:52 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/03 13:32:01 by ddiniz-m         ###   ########.fr       */
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
	while (pos < size && ft_strcmp(arr[pos], "|") != 0)
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

void	set_fd(t_minishell *ms)
{
	dup2(ms->fdout_buf, STDOUT_FILENO);
	close(ms->fdout_buf);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
}
