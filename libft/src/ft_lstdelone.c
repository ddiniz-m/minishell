/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:09:40 by mortins-          #+#    #+#             */
/*   Updated: 2023/07/13 14:54:29 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include"../../inc/minishell.h"

//	Deletes and frees the given node using the function ’del’ and free

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->data);
	free(lst);
}
