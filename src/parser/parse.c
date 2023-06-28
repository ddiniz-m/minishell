/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/28 18:08:22 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_main(t_var *var)
{
	int	i;

	i = 0;
	t_arr	**arr;

	arr_print("MAIN ARRAY", var->main_arr);
	arr = cmd_struct_init(var);
	while(arr[i] && i < var->cmd_count)
	{
		arr_print("COMMAND", arr[i]->cmd);
		if(ft_strcmp("echo", arr[i]->cmd[0]) == 0)
		{
			printf("\nECHO OUTPUT:\n");
			echo(var, arr[i]->cmd);
		}
		else if(ft_strcmp("env", arr[i]->cmd[0]) == 0)
			arr_print("ENV OUTPUT", var->env);
		else if(ft_strcmp("export", arr[i]->cmd[0]) == 0)
			arr_print("EXPORT OUTPUT", export_init(var));
		free_array(arr[i]->cmd);
		i++;
	}
}
