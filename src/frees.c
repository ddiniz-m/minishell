/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:53:12 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/02 15:29:21 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_var(t_var *var)
{
	if (var->str)
		free(var->str);
	if (var->prompt)
		free(var->prompt);
	if (var->main_arr)
		free_array(var->main_arr);
	free(var);
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

void	malloc_error(t_var *var)
{
	write(2, "Error: Malloc failed\n", 22);
	free_var(var);
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