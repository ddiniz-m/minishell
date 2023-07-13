/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:08:15 by mira              #+#    #+#             */
/*   Updated: 2023/07/13 15:06:24 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_init(t_list **list, char **env)
{
	int		i;
	t_list	*node;

	i = 0;
	while (env[i])
	{
		node = ft_lstnew(env[i]);
		ft_lstadd_back(list, node);
		i++;
	}
}