/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:31:09 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/30 16:20:28 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_var(t_var *var)
{
	(void)var;
}

char	*export_str(char *str)
{
	int		i;
	int		j;
	char	*buf1;
	char	*buf2;

	i = 0;
	j = 0;
	buf1 = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	while (str[i] && str[i] != '=')
		buf1[j++] = str[i++];
	buf1[j++] = str[i++];
	buf1[j++] = '\"';
	while (str[i])
		buf1[j++] = str[i++];
	buf1[j] = '\"';
	buf2 = ft_calloc(ft_strlen(buf1) + 12, sizeof(char));
	buf2 = ft_strjoin("declare -x ", buf1);
	free(buf1);
	return (buf2);
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
		ft_strcpy(exp[k], export_str(var->env[i]));
		i++;
	}
	return (exp);
}
//ARG=abc				-> len = 7
//declare -x ARG="abc"	-> len = 7 + 13
