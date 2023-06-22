/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:10:25 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/22 14:50:11 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Takes the main array and creates an array with echo and its respective
//	contents (flags and text)
char	**echo_array(t_var *var, char **arr, int size)
{
	int		pos;
	char	**buf;
	int		echo_size;

	pos = 0;
	while (pos < size)
	{
		if (ft_strncmp("echo", arr[pos], ft_strlen(arr[pos])) == 0)
			break ;
		pos++;
		if (pos == size)
			return (NULL);
	}
	echo_size = echo_cmd_count(var, arr, pos);
	buf = arr_cpy(arr, pos, echo_size);
	return (buf);
}

//Takes main array and creates an array for every valid echo command
t_arr	**echo_struct_init(t_var *var)
{
	int		i;
	t_arr	**arr;
	char	**buf;

	i = 0;
	buf = arr_cpy(var->main_arr, 0, arr_size(var->main_arr));
	arr = malloc(sizeof(t_arr *));
	while (i < var->echo_count)
	{
		arr[i] = malloc(sizeof(t_arr));
		if (arr && arr[i])
			arr[i]->echo = echo_array(var, buf, var->words);
		if (buf)
			buf = buf + arr_size(arr[i]->echo) + 1;
		i++;
	}
	return (arr);
}

int	echo(t_var *var, t_arr **arr, int pos)
{
	int	j;
	int	cmds;
	int	n_flag;

	j = 1;
	n_flag = 0;
	cmds = echo_cmd_count(var, arr[pos]->echo, 0);
	if (arr[pos]->echo && echo_flag(arr[pos]->echo[1]) == 0)
	{
		n_flag = 1;
		j++;
	}
	if (cmds == 1)
		return (printf("\n"));
	while (arr[pos]->echo && j < arr_size(arr[pos]->echo))
	{
		printf("%s", arr[pos]->echo[j++]);
		if (arr[pos]->echo && j != arr_size(arr[pos]->echo))
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
