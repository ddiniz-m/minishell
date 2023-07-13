/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/07/13 16:12:29 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* t_arr	**arr_struct_init(t_var *var)
{
	int	i;
	t_arr	**arr;
	
	arr = malloc(sizeof(t_arr *));
	while (i < var->cmd_count)
		arr[i++] = malloc(sizeof(t_arr));
	return (arr);
} */

t_var	*var_struct_init(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	return (var);
}

void	var_init(t_var *var)
{
	var->words = 0;
	str_words(var, var->str);
	var->main_arr = split_main(var, var->str);
	var->cmd_count = cmd_count(var, var->main_arr);
	printf("Cmd Count = %i\n", var->cmd_count);
}
