/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/19 19:23:01 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parse_main(t_var *var, char *str)
{
	int	i;
	t_arr	**arr;
	char	**buf;

	i = 0;
	printf("Number of words = %i\n", var->words);
	buf = split_main(var, str);
	arr_print("MAIN ARRAY", buf);
	printf("echo count = %i\n", echo_count(var, buf));
	if (echo_count(var, buf) > 0)
	{
		arr = echo_struct_init(var, buf);
		while (i < echo_count(var, buf))
		{
			arr_print("Echo Array", arr[i]->echo);
			i++;
		}
	}
}
