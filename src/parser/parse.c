/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/08/02 15:37:11 by mira             ###   ########.fr       */
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
		{
			list_sort(exp);
			if (arr_size(arr[i]->cmd) > 1)
				export(arr[i]->cmd, exp, env);
			else
			{
				printf("EXPORT OUTPUT\n");
				list_print(exp);
			}
		}
		else if(ft_strcmp("unset", arr[i]->cmd[0]) == 0)
		{
			if (arr_size(arr[i]->cmd) > 1)
			{
				unset(env, exp, arr[i]->cmd);
			}
			else
				break ;
		}
		i++;
	}
	free(arr);
}
