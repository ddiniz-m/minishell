/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:58:56 by mortins-          #+#    #+#             */
/*   Updated: 2023/07/13 15:40:20 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include"../../inc/minishell.h"

//	Counts the number of nodes in a list

int	ft_lstsize(t_list *lst)
{
	int	count;
	t_list	*tmp;

	count = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp -> next;
		count++;
	}
	return (count);
}
