/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/16 19:06:39 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parse_echo(t_var *var, char **Arr)
{
	int		i;
	int		j;
	char	**buf;
	t_arr	**arr;
	int		echo_count;

	
	i = 0;
	j = 0;
	buf = arr_cpy(Arr);
	arr = malloc(sizeof(t_arr *));
	echo_count = echo_n(buf, var->words);
	printf("Number of valid echo commands = %i\n", echo_count);
	while (i < echo_count)
	{
		arr[i] = malloc(sizeof(t_arr));
		arr[i]->echo = echo_arr(buf, var->words);
		if (buf)
			buf = buf + arr_size(arr[i]->echo) + 1;
		i++;
	}
	i = 0;
	while (arr[i] && i < echo_n(Arr, var->words))
	{
		j = 0;
		printf("\nEcho Array %i:\n", i + 1);
		while(arr[i]->echo[j] && j < arr_size(arr[i]->echo))
		{
			printf("%s\n", arr[i]->echo[j]);
			j++;
		}
		i++;
	}
}

void	parse_main(t_var *var, char *str)
{
	int		i;
	char	**buf;

	i = 0;
	printf("Number of words = %i\n", var->words);
	printf("------------------------------------MAIN STR ARRAY------------------------------------\n");
	buf = split(var, str);
	while(i < var->words)
		printf("%s\n", buf[i++]);
	printf("\n");
	if (echo_n(buf, var->words) > 0)
		parse_echo(var, buf);
}