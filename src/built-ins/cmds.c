/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:10:25 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/06 17:02:01 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Takes the main array and creates an array with a command and its respective
//	arguments/options
char	**cmd_array(t_var *var, char **arr, int size)
{
	int		i;
	char	**buf;
	int		cmd_size;

	i = 0;
	while (i < size)
	{
		if (cmd_validate(arr[i]) == 1)
			break ;
		i++;
		if (i == size)
			return (NULL);
	}
	cmd_size = cmd_args(var, arr, i);
	buf = arr_cpy(arr, i, cmd_size);
	return (buf);
}

//Takes main array and creates an array for every valid command
t_arr	**cmd_struct_init(t_var *var)
{
	int		i;
	t_arr	**arr;
	char	**buf;
	i = 0;
	buf = arr_cpy(var->main_arr, 0, arr_size(var->main_arr));
	arr = malloc(sizeof(t_arr *));
	while (i < var->cmd_count)
	{
		arr[i] = malloc(sizeof(t_arr));
		if (arr && arr[i])
			arr[i]->cmd = cmd_array(var, buf, var->words);
		if (buf)
			buf =  buf + arr_size(arr[i]->cmd) + 1;
		i++;
	}
	return (arr);
}
