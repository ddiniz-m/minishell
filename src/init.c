/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/28 16:43:05 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_var	*var_struct_init(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	return (var);
}

void	var_init(t_var *var, char **env)
{
	var->words = 0;
	str_words(var, var->str);
	var->env = env;
	var->main_arr = split_main(var, var->str);
	var->cmd_count = cmd_count(var, var->main_arr);
	printf("Cmd Count = %i\n", var->cmd_count);
}
