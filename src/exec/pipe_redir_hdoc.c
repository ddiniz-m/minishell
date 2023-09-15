/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_hdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:43:52 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/15 13:51:20 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_redir_hdoc(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		while(!ft_strcmp(arr[i], ">"))
		{
			
		}
		while(!ft_strcmp(arr[i], ">>"))
		{
			
		}
		while(!ft_strcmp(arr[i], "<"))
		{
			
		}
		while(!ft_strcmp(arr[i], "<<"))
		{
			
		}
	}
	
}