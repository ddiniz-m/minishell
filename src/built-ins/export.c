/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:31:09 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/28 18:08:45 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export(t_var *var)
{
	(void)var;
}

char	**export_init(t_var *var)
{
	int		i;
	int		j;
	int		k;
	char	**exp;
	
	i = 0;
	exp = ft_calloc(arr_size(var->env) + 1, sizeof(char *));
	while (i < arr_size(var->env))
	{
		j = 0;
		k = 0;
		while (j < arr_size(var->env))
		{
			if (ft_strcmp(var->env[i], var->env[j]) > 0)
				k++;
			j++;
		}
		exp[k] = ft_calloc(ft_strlen(var->env[i]) + 1, sizeof(char));
		ft_strcpy(exp[k], var->env[i]);
		i++;
	}
	return (exp);
}