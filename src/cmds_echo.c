/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:10:25 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/20 16:31:48 by ddiniz-m         ###   ########.fr       */
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

//Takes the main array and creates an array with echo and its respective contents (flags and text)
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
	printf("Number of valid echo commands = %i\n", var->echo_count);
	while (i < var->echo_count)
	{
		arr[i] = malloc(sizeof(t_arr));
		arr[i]->echo = echo_array(var, buf, arr_size(buf));
		buf = buf + arr_size(arr[i]->echo) + 1;
		i++;
	}
	return (arr);
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

void	echo(t_var *var, t_arr **arr, int pos)
{
	int	j;
	int	cmds;
	int	n_flag;

	j = 1;
	n_flag = 0;
	cmds = echo_cmd_count(var, arr[pos]->echo, 0);
	if(arr[pos]->echo && echo_flag(arr[pos]->echo[1]) == 0)
	{
		n_flag = 1;
		j++;
	}
	if (cmds == 1)
	{
		printf("\n");
		return ;
	}
	while (arr[pos]->echo && j < arr_size(arr[pos]->echo))
	{
		printf("%s", arr[pos]->echo[j]);
		j++;
		if (arr[pos]->echo && j != arr_size(arr[pos]->echo))
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
}

