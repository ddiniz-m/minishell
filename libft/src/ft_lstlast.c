/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:44:55 by mortins-          #+#    #+#             */
/*   Updated: 2023/07/13 14:48:19 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include"../../inc/minishell.h"

//	Returns the last node of the list 'lst'

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
