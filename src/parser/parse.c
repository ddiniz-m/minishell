/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/21 11:26:54 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_main(t_cmdlist *cmd, t_list **env, t_list **exp)
{
	int		i;
	char	**arr;

	i = 0;
	while (cmd)
	{
		arr = cmd->content->cmd_flags;
		arr_print("ARR", arr);
		if (ft_strcmp("env", arr[0]) == 0)
			list_print(env);
		else if (ft_strcmp("export", arr[0]) == 0)
		{
			list_sort(exp);
			if (export_error(arr))
				break ;
			if (arr_size(arr) > 1)
				export(arr, exp, env);
			else
				list_print(exp);
		}
		else if (ft_strcmp("unset", arr[0]) == 0)
		{
			if (arr_size(arr) > 1)
			{
				unset(env, exp, arr);
			}
			else
				break ;
		}
		cmd = cmd->next;
	}
}
