/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/12 15:35:16 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Ja ponho noutro ficehiro, ok?
t_list	*in_lst(char **arr)
{
	int		i;
	t_list	*node;
	t_list	*input;

	i = 0;
	input = NULL;
	while (arr[i])
	{
		if (arr[i + 1] && (!ft_strcmp(">", arr[i]) || !ft_strcmp(">>", arr[i])))
		{
			node = ft_lstnew(arr[i + 1]);
			if (!node)
			{
				ft_lstclear(&input, free);
				return (NULL);
			}
			ft_lstadd_back(&input, node);
		}
		i++;
	}
	return (input);
}

t_list	*out_lst(char **arr)
{
	int		i;
	t_list	*node;
	t_list	*output;

	i = 0;
	output = NULL;
	while (arr[i])
	{
		if (arr[i + 1] && (!ft_strcmp("<", arr[i]) || !ft_strcmp("<<", arr[i])))
		{
			node = ft_lstnew(arr[i + 1]);
			if (!node)
			{
				ft_lstclear(&output, free);
				return (NULL);
			}
			ft_lstadd_back(&output, node);
		}
		i++;
	}
	return (output);
}

t_content	*content_init(t_minishell *ms, int cmd_index)
{
	t_content *content;
	
	content = malloc(sizeof(t_content));
	
	if (cmd_index != 0)
		cmd_index += cmd_args(ms->main_arr, cmd_index) + 1;
	
	content->cmd_flags = cmd_with_flags(ms->main_arr, cmd_index);
	content->cmd_path = "PATH";
	content->input = in_lst(ms->main_arr);
	content->output = out_lst(ms->main_arr);
	return (content);
}

//Creates cmdlist. Initializes content by calling content_init. Similar to ft_lstnew.
t_cmdlist	*cmdlist_lstnew(t_minishell *ms, int cmd_index)
{
	t_cmdlist	*cmdlist;

	cmdlist = malloc(sizeof(t_cmdlist));
	if (!cmdlist)
		return (NULL);
	cmdlist->content = content_init(ms, cmd_index);
	cmdlist->next = NULL;
	return (cmdlist);
}

t_cmdlist	*cmd_list_init(t_minishell *ms)
{
	int			i;
	t_cmdlist	*node;
	t_cmdlist	*cmdlist;

	i = 0;
	printf("\nCMD_COUNT = %i\n", ms->cmd_count);
	if (ms->cmd_count <= 0)
		return (NULL);
	cmdlist = NULL;
	while (i < ms->cmd_count)
	{
		node = cmdlist_lstnew(ms, i);
		cmd_lstadd_back(&cmdlist, node);
		i++;
	}
	return (cmdlist);
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
