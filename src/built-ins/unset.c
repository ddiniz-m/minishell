/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:54:07 by mira              #+#    #+#             */
/*   Updated: 2023/09/05 16:39:22 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset(t_list **env, t_list **exp, char **arr)
{
	int		i;
	int		j;
	char	*buf;
	t_list	*tmp;

	i = 1;
	tmp = *env;
	while (i < arr_size(arr))
	{
		j = 0;
		if (env_check_dup(arr[i], env) == 0)
		{
			while (j < list_size(env) - 1)
			{
				printf("UNSET arr[%i] = %s\ntmp->data = %s\n", i, arr[i], tmp->data);
				if (strcmp_chr(arr[i], tmp->data, '=') == 0
					|| ft_strcmp(arr[i], tmp->data) == 0)
				{
					printf("UNSET 4!!!\n");
					list_remove(env, j);
				}
				tmp = tmp->next;
				j++;
			}
		}
		if (export_check_dup(arr[i], exp) == 0)
		{
			buf = export_str(arr[i]);
			while (j < list_size(exp) - 1)
			{
				if (strcmp_chr(buf, tmp->data, '=') == 0
					|| ft_strcmp(buf, tmp->data) == 0)
					list_remove(exp, j);
				tmp = tmp->next;
				j++;
			}
		}
		i++;
	}
}
