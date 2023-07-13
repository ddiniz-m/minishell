/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/07/13 18:55:09 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_main(t_var *var, t_list **env, t_list **exp)
{
	int		i;
	t_arr	**arr;

	i = 0;
	arr = cmd_struct_init(var);
	arr_print("MAIN ARRAY", var->main_arr);
	while(i < var->cmd_count)
	{
		arr_print("COMMAND", arr[i]->cmd);
		if(ft_strcmp("env", arr[i]->cmd[0]) == 0)
		{
			printf("ENV OUTPUT\n");
			list_print(env);
		}
		else if(ft_strcmp("export", arr[i]->cmd[0]) == 0)
			export(arr, exp, env);
		/* else if(ft_strcmp("unset", arr[i]->cmd[0]) == 0)
		{
			if (arr_size(arr[i]->cmd) > 1)
			{
				int	j = 1;
				int	size = arr_size(arr[i]->cmd);
				while (j < size)
					ft_lstadd_back(export, export_listnew( arr[i]->cmd[j++]));
			}
			else
				break ;
		} */
		i++;
	}
	free(arr);
}
