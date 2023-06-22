/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_echo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:54:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/22 14:50:07 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Counts how many valid echo commands there are
int	echo_count(t_var *var, char **arr)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < var->words)
	{
		if (arr[i] && ft_strncmp("echo", arr[i], ft_strlen(arr[i])) == 0)
			n++;
		while (arr && arr[i] && arr[i][0] && meta_char(arr[i][0]) != 2)
			i++;
		i++;
	}
	return (n);
}

//Counts how many flags/words echo will use/print, beginning at echo's position
int	echo_cmd_count(t_var *var, char **arr, int pos)
{
	int	i;

	i = 0;
	while (arr[i] && pos < var->words)
	{
		pos++;
		if (!arr[i] || meta_char(arr[i][0]) == 2)
			return (i);
		i++;
	}
	return (i);
}

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
