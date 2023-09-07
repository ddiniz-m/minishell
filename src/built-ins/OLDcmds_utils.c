/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:54:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/08/04 15:11:22 by mira             ###   ########.fr       */
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

//Counts how many flags/arguments the fisrt command will use/print
int	cmd_args(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && i < arr_size(arr))
	{
		if (meta_char(arr[i][0]) == 2)
			break ;
		i++;
	}
	return (i - 1);
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