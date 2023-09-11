/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/11 13:45:13 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmdlist_print(t_cmdlist **cmdlist)
{
	int	i;
	t_cmdlist	*tmp;


	i = 1;
	tmp = *cmdlist;
	printf("\nLIST:\n");
	while (tmp)
	{
		printf("	NODE%i:\n", i);
		printf("		CONTENT:\n");
		printf("		Command: %s\n", tmp->content->cmd);
		arr_print("	Command with flags", tmp->content->cmd_flags);
		printf("		Input: %s\n", tmp->content->input);
		printf("		Output: %s\n",tmp->content->output);
		i++;
		tmp = tmp->next;
	}
}

t_content	*content_init(t_minishell *ms, int n_cmds)
{
	t_content *content;
	
	content = malloc(sizeof(t_content));
	
	if (n_cmds != 0)
		n_cmds += cmd_args(ms->main_arr, n_cmds) + 1;
	
	content->cmd_flags = cmd_with_flags(ms->main_arr, n_cmds);
	content->cmd = "ABC";
	content->input = "ABC";
	content->output = "DEF";
	return (content);
}

//Creates cmdlist. Initializes content by calling content_init. Similar to ft_lstnew.
t_cmdlist	*cmdlist_lstnew(t_minishell *ms, int n_cmds)
{
	t_cmdlist *cmdlist;

	cmdlist = malloc(sizeof(t_cmdlist));
	if (!cmdlist)
		return (NULL);
	cmdlist->content = content_init(ms, n_cmds);
	cmdlist->next = NULL;
	return (cmdlist);
}

t_cmdlist	*cmd_list_init(t_minishell *ms)
{
	int			i;
	t_cmdlist	*node;
	t_cmdlist	**cmdlist;

	i = 0;
	printf("\nCMD_COUNT = %i\n", ms->cmd_count);
	if (ms->cmd_count <= 0)
		return (NULL);
	cmdlist = malloc(sizeof(t_cmdlist));
	*cmdlist = NULL;
	while (i < ms->cmd_count)
	{
		node = cmdlist_lstnew(ms, i);
		cmd_lstadd_back(cmdlist, node);
		i++;
	}
	return (*cmdlist);
}

t_minishell	*struct_init(void)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	return (ms);
}

void	var_init(t_minishell *ms)
{
	ms->words = 0;
	str_counter(ms, ms->str);
	ms->main_arr = split_main(ms, ms->str);
	ms->cmd_count =  cmd_count(ms, ms->main_arr);
	ms->cmdlist = cmd_list_init(ms);
	cmdlist_print(&ms->cmdlist);
}
