/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:29:16 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/20 17:18:20 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit(t_minishell *ms, char *arg)
{
	if (arg && arg[0])
	{
		if (0 <= ft_atoi(arg) && ft_atoi(arg) <= 255)
			EXIT_STATUS = ft_atoi(arg);
	}
	printf("exit\n");
	free_ms(ms);
	exit (EXIT_STATUS);
}