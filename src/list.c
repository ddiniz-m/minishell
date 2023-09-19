/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:53:08 by mira              #+#    #+#             */
/*   Updated: 2023/09/06 16:55:04 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// parses list and checks if there is any data that is equal to the string
// Returns position of duplicate if sucessful. Returns 0 otherwise.
int	list_check_dup(t_list **list, char *str)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *list;
	while (tmp)
	{
		if (ft_strcmp(tmp->data, str) == 0)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

void	list_swap(t_list *list)
{
	char	*str;
	t_list	*head;
	t_list	*tmp;

	str = NULL;
	head = list;
	if (!head && !head->next)
	{
		printf("List Swap Error\n");
		return ;
	}
	tmp = head;
	str = tmp->data;
	head->data = head->next->data;
	head->next->data = str;
}

void	list_remove(t_list **list, int pos)
{
	int		i;
	t_list	*tmp;
	t_list	*target;

	i = 0;
	tmp = *list;
	if (pos == 0)
	{
		(*list) = (*list)->next;
		return ;
	}
	while (i < pos - 1)
	{
		tmp = tmp->next;
		i++;
	}
	target = tmp->next;
	tmp->next = target->next;
	free(target);
}

void	list_sort(t_list **list)
{
	t_list	*head;
	t_list	*tmp;

	head = *list;
	tmp = head;
	while (tmp)
	{
		while (head->next)
		{	
			if (ft_strcmp(head->data, head->next->data) > 0)
				list_swap(head);
			head = head->next;
		}
		tmp = tmp->next;
		head = *list;
	}
}

void	list_print(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}

int	list_size(t_list **list)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}