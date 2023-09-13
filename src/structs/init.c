/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/13 11:20:02 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*in_lst(char **arr, int cmd_index) // inteprets both `<` and `<<`
{
	t_list	*node;
	t_list	*input;

	input = NULL;
	while (arr[cmd_index] && arr[cmd_index][0] == '<')
	{
		if (arr[cmd_index + 1])
		{
			node = ft_lstnew(arr[cmd_index + 1]);
			if (!node)
			{
				ft_lstclear(&input, free);
				return (NULL);
			}
			ft_lstadd_back(&input, node);
		}
		cmd_index += 2;
	}
	return (input);
}

t_list	*out_lst(char **arr, int cmd_index) // inteprets both `>` and `>>`
{
	t_list	*node;
	t_list	*output;

	output = NULL;
	while (arr[cmd_index] && !ft_strrchr(">|", arr[cmd_index][0]))
		cmd_index++;
	while (arr[cmd_index] && arr[cmd_index][0] == '>')
	{
		if (arr[cmd_index + 1])
		{
			node = ft_lstnew(arr[cmd_index + 1]);
			if (!node)
			{
				ft_lstclear(&output, free);
				return (NULL);
			}
			ft_lstadd_back(&output, node);
		}
		cmd_index += 2;
	}
	return (output);
}

t_content	*content_init(t_minishell *ms, int cmd_index)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	content->input = in_lst(ms->main_arr, cmd_index);
	while (ms->main_arr[cmd_index] && ms->main_arr[cmd_index][0] == '<' &&
		ms->main_arr[cmd_index + 1])
		cmd_index += 2;
	content->cmd_flags = cmd_with_flags(ms->main_arr, cmd_index);
	content->output = out_lst(ms->main_arr, cmd_index);
	content->cmd_path = "PATH";
	return (content);
}

//Creates cmdlist. Initializes content by calling content_init.
//Similar to ft_lstnew.
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
	int			cmd_n;
	int			i;
	int			a;
	t_cmdlist	*node;
	t_cmdlist	*cmdlist;

	i = 0;
	cmd_n = 0;
	a = 0;
	printf("\nCMD_COUNT = %i\n", ms->cmd_count); //extra line
	if (ms->cmd_count <= 0)
		return (NULL);
	cmdlist = NULL;
	while (cmd_n < ms->cmd_count)
	{
		node = cmdlist_lstnew(ms, i);
		if (node->content->input)
			i += (ft_lstsize(node->content->input) * 2);
		if (node->content->output)
			i += (ft_lstsize(node->content->output) * 2);
		i += arr_size(node->content->cmd_flags) + 1;
		cmd_lstadd_back(&cmdlist, node);
		cmd_n++;
	}
	return (cmdlist);
}

void	var_init(t_minishell *ms)
{
	ms->words = 0;
	str_counter(ms, ms->str);
	ms->main_arr = split_main(ms, ms->str);
	ms->cmd_count = cmd_count(ms, ms->main_arr);
	ms->cmdlist = cmd_list_init(ms);
	cmdlist_print(&ms->cmdlist);
}
