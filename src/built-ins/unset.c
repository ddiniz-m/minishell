/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:54:07 by mira              #+#    #+#             */
/*   Updated: 2023/09/14 12:49:16 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//strlen until c
int	strlen_chr(char *str, char c)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != c)
		i++;
	return (i);
}

//Compares strings until s1 reaches c
int	strcmp_chr(char *s1, char *s2, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < strlen_chr(s2, c))
	{
		n += s1[i] - s2[i];
		i++;
	}
	return (n);
}

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