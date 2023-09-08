/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:08:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/08 17:08:51 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

//Counts how many flags/arguments the fisrt command will use/print
int	cmd_args(char **arr, int pos)
{
	while (arr[pos] && pos < arr_size(arr))
	{
		if (meta_char(arr[pos][0]) == 2)
			break ;
		pos++;
	}
	return (pos - 1);
}

//Counts how many valied commands there are in main->arr.
int	cmd_count(t_minishell *ms, char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ms->words)
	{
		if (arr[i] && cmd_validate(arr[i]) == 1)
			j++;
		while (arr && arr[i] && arr[i][0] && meta_char(arr[i][0]) != 2)
			i++;
		i++;
	}
	return (j);
}