/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:10:25 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/19 19:22:49 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		while (arr[i] && arr[i][0] && meta_char(arr[i][0]) != 2)
			i++;
		i++;
	}
	return (n);
}

//Counts how many flags/words echo will use/print, beginning at echo's position
int	echo_word_count(t_var *var, char **arr, int pos)
{
	int	i;

	i = 0;
	while (pos < var->words)
	{
		i++;
		pos++;
		if (arr[pos] && arr[pos][0] && (meta_char(arr[pos][0]) == 2))
			return (i);
	}
	return (i);
}

//Creates an array with echo and its respective contents (flags and text)
char	**echo_array(t_var *var, char **arr)
{
	int		pos;
	char	**buf;
	int		echo_size;

	pos = 0;
	while (pos < var->words)
	{
		if (ft_strncmp("echo", arr[pos], ft_strlen(arr[pos])) == 0)
			break ;
		pos++;
		if (pos == var->words)
			return (NULL);
	}
	echo_size = echo_word_count(var, arr, pos);
	buf = arr_cpy(arr, pos, echo_size);
	return (buf);
}

//Takes main array and creates an array for every valid echo command
t_arr	**echo_struct_init(t_var *var, char **main_arr)
{
	int		i;
	t_arr	**arr;
	char	**buf;
	int		echo_n;

	i = 0;
	buf = arr_cpy(main_arr, 0, arr_size(main_arr));
	arr = malloc(sizeof(t_arr *));
	echo_n = echo_count(var, main_arr);
	printf("Number of valid echo commands = %i\n", echo_n);
	while (i < echo_n)
	{
		arr[i] = malloc(sizeof(t_arr));
		arr[i]->echo = echo_array(var, buf);
		buf = buf + arr_size(arr[i]->echo) + 1;
		i++;
	}
/* 	//print arrays
	i = 0;
	while (i < echo_n)
		arr_print("ECHO ARRAY", arr[i++]->echo); */
	return (arr);
}
