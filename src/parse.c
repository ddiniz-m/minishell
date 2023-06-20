/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/20 18:30:56 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parse_main(t_var *var)
{
	int		i;
	t_arr	**arr;

	i = 0;
	arr_print("MAIN ARRAY", var->main_arr);
	if (var->echo_count > 0)
	{
		arr = echo_struct_init(var);
		printf("\nECHO OUTPUT\n");
		echo(var, arr, 0);
		arr_free(arr[0]->echo);
		free(arr);
	}
}
