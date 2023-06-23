/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:56:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/23 18:57:28 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (1);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	echo(t_var *var, char **echo)
{
	int	j;
	int	cmds;
	int	n_flag;

	j = 1;
	n_flag = 0;
	cmds = cmd_args(var, echo, 0);
	if (echo && echo_flag(echo[1]) == 0)
	{
		n_flag = 1;
		j++;
	}
	if (cmds == 1)
		return (printf("\n"));
	while (echo && j < arr_size(echo))
	{
		printf("%s", echo[j++]);
		if (echo && j != arr_size(echo))
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
