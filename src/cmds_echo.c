/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:10:25 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/19 16:57:57 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//counts how many valid echo commands there are
int	echo_count(char **arr, int words)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < words)
	{
		if (arr[i] && ft_strncmp("echo", arr[i], ft_strlen(arr[i])) == 0)
			n++;
		while (arr[i] && meta_char(arr[i][0]) != 2)
			i++;
		i++;
	}
	return (n);
}

//counts how many flags/words echo will use/print, beginning at echo's position
int	echo_word_count(char **arr, int pos, int words)
{
	int	i;

	i = 0;
	while (pos < words)
	{
		i++;
		pos++;
		if (arr[pos] && meta_char(arr[pos][0]) == 2)
			return (i);
	}
	return (i);
}

//creates an array with echo and its respective contents (flags and text)
char	**echo_array(char **arr, int words)
{
	int		pos;
	char	**buf;
	int		echo_size;

	pos = 0;
	while (pos < words)
	{
		if (ft_strncmp("echo", arr[pos], ft_strlen(arr[pos])) == 0)
			break ;
		pos++;
		if (pos == words)
			return (NULL);
	}
	echo_size = echo_word_count(arr, pos, words);
	buf = arr_cpy(arr, pos, echo_size);
	return (buf);
}

//Takes main array and creates an array for every valid echo command
void	echo_struct_init(t_var *var, char **Arr)
{
	int		i;
	char	**buf;
	t_arr	**arr;
	int		echo_n;

	i = 0;
	buf = arr_cpy(Arr, 0, arr_size(Arr));
	arr = malloc(sizeof(t_arr *));
	echo_n = echo_count(buf, var->words);
	printf("Number of valid echo commands = %i\n", echo_n);
	while (i < echo_n)
	{
		arr[i] = malloc(sizeof(t_arr));
		arr[i]->echo = echo_array(buf, arr_size(buf));
		if (buf[i] && buf[i + 1])
			buf = buf + arr_size(arr[i]->echo) + 1;
		i++;
	}
}
