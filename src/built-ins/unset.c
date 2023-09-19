/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:54:07 by mira              #+#    #+#             */
/*   Updated: 2023/09/19 15:25:07 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_env(t_list **env, char *str)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *env;
	while (i < ft_lstsize(*env))
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
	while (i < ft_lstsize(*exp))
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
	char	*exp_buf;
	
	i = 1;
	while (i < arr_size(arr))
	{
		buf = ft_strdup(arr[i]);
		if (env_check_dup(buf, env) == 0)
			unset_env(env, buf);
		exp_buf = export_str(buf);
		if (export_check_dup(exp_buf, exp) == 0)
			unset_exp(exp, exp_buf);
		i++;
		free(exp_buf);
	}
}