/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:54:07 by mira              #+#    #+#             */
/*   Updated: 2023/09/06 16:53:50 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_env(t_list **env, char *str)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *env;
	while (i < list_size(env))
	{
		if (strcmp_chr(str, tmp->data, '=') == 0
			|| ft_strcmp(str, tmp->data) == 0)
		{
			list_remove(env, i);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
}

void	unset_exp(t_list **exp, char *str)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *exp;
	while (i < list_size(exp))
	{
		if (strcmp_chr(str, tmp->data, '=') == 0
			|| ft_strcmp(str, tmp->data) == 0)
		{
			list_remove(exp, i);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
}

void	unset(t_list **env, t_list **exp, char **arr)
{
	int		i;
	char	*buf;
	
	i = 1;
	while (i < arr_size(arr))
	{
		if (env_check_dup(arr[i], env) == 0)
			unset_env(env, arr[i]);
		buf = export_str(arr[i]);
		if (export_check_dup(buf, exp) == 0)
			unset_exp(exp, buf);
		i++;
		free(buf);
	}
}