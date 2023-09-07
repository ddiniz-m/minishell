/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:53:12 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/07 17:31:38 by ddiniz-m         ###   ########.fr       */
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

void	free_list(t_list **list, int flag)
{
	t_list	*head;
	t_list	*temp;

	head = *list;
	while (head)
	{
		temp = head;
		head = head->next;
		if (!flag)
			free(temp->data);
		free(temp);
	}
	free(list);
}