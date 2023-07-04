/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/07/04 17:56:53 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_main(t_var *var)
{
	int	i;
	t_arr	**arr;
	char	**export;

	i = 0;
	arr_print("MAIN ARRAY", var->main_arr);
	arr = cmd_struct_init(var);
	while(arr[i] && i < var->cmd_count)
	{
		arr_print("COMMAND", arr[i]->cmd);
		if(ft_strcmp("env", arr[i]->cmd[0]) == 0)
			arr_print("ENV OUTPUT", var->env);
		else if(ft_strcmp("export", arr[i]->cmd[0]) == 0)
		{
			if (arr_size(arr[i]->cmd) == 1)
			{
				export = export_init(var);
				arr_print("EXPORT OUTPUT", export);
				free_array(export);
			}
			else
				export_var(var);
		}
		free_array(arr[i]->cmd);
		free(arr[i]);
		i++;
	}
	free(arr);
}
