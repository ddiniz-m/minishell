/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:53:12 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/11 10:35:00 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_ms(t_minishell *ms)
{
	if (ms->str)
		free(ms->str);
	if (ms->prompt)
		free(ms->prompt);
	if (ms->main_arr)
		free_array(ms->main_arr);
	free(ms);
	exit (0);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && i < arr_size(arr))
		free(arr[i++]);
	free(arr);
}

void	malloc_error(t_minishell *ms)
{
	write(2, "Error: Malloc failed\n", 22);
	free_ms(ms);
}

void	free_list(t_list **list)
{
	t_list	*head;
	t_list	*tmp;

	head = *list;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->data);
		free(tmp);
	}
}

void	free_cmd_list(t_cmdlist *cmdlist)
{
	t_cmdlist	*tmp;
	t_cmdlist	*head;

	head = cmdlist;
	while (head)
	{
		tmp = head;
		head = head->next;
		//free(tmp->content->cmd)
		//etc...
		free(tmp->content);
		free(tmp);
	}
}