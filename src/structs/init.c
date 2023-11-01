/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/01 17:12:41 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Might have to change how we handle content->heredoc, depending on our
// solution for heredoc
t_content	*content_init(t_minishell *ms, int cmd_index)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	content->input = redir_lst(ms->main_arr, cmd_index, "<");
	content->output = redir_lst(ms->main_arr, cmd_index, ">");
	content->append = redir_lst(ms->main_arr, cmd_index, ">>");
	content->cmd_flags = cmd_with_flags(ms, ms->main_arr, cmd_index);
	return (content);
}

//Creates cmdlist. Initializes content by calling content_init.
//Similar to ft_lstnew.
t_cmdlist	*cmdlist_lstnew(t_minishell *ms, int cmd_index)
{
	t_cmdlist	*cmdlist;

	cmdlist = malloc(sizeof(t_cmdlist));
	if (!cmdlist)
		malloc_error(ms);
	cmdlist->content = content_init(ms, cmd_index);
	cmdlist->next = NULL;
	return (cmdlist);
}

t_cmdlist	*cmd_list_init(t_minishell *ms)
{
	int			cmd_n;
	int			i;
	t_cmdlist	*node;
	t_cmdlist	*cmdlist;

	i = 0;
	cmd_n = 0;
	if (ms->cmd_count <= 0)
		return (NULL);
	cmdlist = NULL;
	while (cmd_n < ms->cmd_count)
	{
		node = cmdlist_lstnew(ms, i);
		while (ms->main_arr[i] && ft_strcmp(ms->main_arr[i], "|") != 0)
			i++;
		if (ms->main_arr[i] && ft_strcmp(ms->main_arr[i], "|") == 0)
			i++;
		ft_lstadd_back((t_list **)&cmdlist, (t_list *)node);
		cmd_n++;
	}
	return (cmdlist);
}

void	var_init(t_minishell *ms)
{
	ms->cmd_in_fd = 0;
	ms->fdin_buf = dup(STDIN_FILENO);
	ms->fdout_buf = dup(STDOUT_FILENO);
	ms->main_arr = split_main(ms, ms->str);
	ms->cmd_count = cmd_count(ms->main_arr);
	init_heredoc(ms, ms->main_arr);
	env_var(ms, ms->env, ms->main_arr);
	ms->cmdlist = cmd_list_init(ms);
}
