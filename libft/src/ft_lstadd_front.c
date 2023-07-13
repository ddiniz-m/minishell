/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:07:21 by mortins-          #+#    #+#             */
/*   Updated: 2023/07/11 15:39:28 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include"../../inc/minishell.h"

//	Adds the node ’new’ at the beginning of the list 'lst'

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}
