/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:01:33 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/19 16:29:14 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

//	Applies the function ’f’ on the content of each node
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}
