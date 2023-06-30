/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:54:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/23 18:57:51 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Counts how many valid commands there are
int	cmd_count(t_var *var, char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < var->words)
	{
		if (arr[i] && cmd_validate(arr[i]) == 1)
			j++;
		while (arr && arr[i] && arr[i][0] && meta_char(arr[i][0]) != 2)
			i++;
		i++;
	}
	return (j);
}

//Counts how many flags/arguments a command will use/print, beginning at 
//	command's position
int	cmd_args(t_var *var, char **arr, int pos)
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

// Checks if str is a valid command
int	cmd_validate(char *str)
{
	if (ft_strcmp("echo", str) == 0 ||
		ft_strcmp("cd", str) == 0 ||
		ft_strcmp("pwd", str) == 0 ||
		ft_strcmp("unset", str) == 0 ||
		ft_strcmp("env", str) == 0 ||
		ft_strcmp("export", str) == 0 ||
		ft_strcmp("exit", str) == 0)
		return (1);
	return (0);
}