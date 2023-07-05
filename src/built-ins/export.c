/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:31:09 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/07/05 14:17:23 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_var(t_var *var)
{
	(void)var;
}

// takes str and creates new string in specific format
// E.g.: str = ARG=123; -> new_str = declare -x ARG="123";
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
	buf2 = ft_strjoin("declare -x ", buf1);
	free(buf1);
	return (buf2);
}

// Creates exp array by sorting and editing env
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
		exp[k] = export_str(var->env[i]);
		i++;
	}
	return (exp);
}
