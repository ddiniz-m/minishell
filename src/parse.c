/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/20 15:03:28 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parse_main(t_var *var)
{
	int	i;
	t_arr	**arr;

	i = 0;
	/* printf("Number of words = %i\n", var->words); */
	arr_print("MAIN ARRAY", var->main_arr);
	/* printf("echo count = %i\n", var->echo_count); */
	if (var->echo_count > 0)
	{
		arr = echo_struct_init(var);
		/* while (arr && arr[i] && arr[i]->echo && arr[i] && i < var->echo_count)
		{
			arr_print("Echo Array", arr[i]->echo);
			i++;
		} */
		printf("\nECHO OUTPUT\n");
		echo(var, arr, 0);
	}
}
