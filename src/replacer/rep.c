/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:37:02 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/04 15:02:28 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
char	**var_split(char *str);

// So, the ideia is to only replace the env variables, not dealing with quotes.
// To do so, we need to check first if the var is inside single quotes, beacuse
//	when it's inside double quotes, it gets repalced all the same.
// I'm thinking in making a function that checks whether there is a $ inside quotes;

int	var_len(char *str)
{
	int	i;

	i = 0;
	if (meta_char(str[i]) == 4)
		i++;
	while(str[i])
	{
		if (meta_char(str[i]) != 0) // more/less conditions?
			return (i);
		i++;
	}
	return (i);
}

void	rep(t_minishell *ms)
{
	int		i;
	int		size;
	int		str_size;
	int		j;
	int		var_size;
	int		buf_size;
	
	char	*pre;
	char	*var;
	char	*buf;
	char	*buf1;
	char	*replaced_var;
	
	i = 0;
	buf = NULL;
	buf1 = NULL;
	j = 0;
	buf_size = 0;
	var_size = 0;
	size = arr_size(ms->main_arr);
	while (i < size)
	{
		j = 0;
		str_size = ft_strlen(ms->main_arr[i] + 1);
		if (ft_strchr(ms->main_arr[i], '$') == 0)
		{
			i++;
			continue;
		}
		while (j < str_size)
		{
			j = strlen_chr(ms->main_arr[i], '$');
			pre = ft_strndup(ms->main_arr[i], j);
			printf("pre: %s\n", pre);

			var_size = var_len(ms->main_arr[i] + j + 1) + 1;
			var = ft_strndup(ms->main_arr[i] + j, var_size);
			printf("var: %s\n", var);

			replaced_var = var_iter(ms->env, var + 1);
			free(var);
			buf = ft_strjoin(pre, replaced_var);
			free(pre);
			free(replaced_var);

			buf1 = ft_strjoin(buf1, buf);
			free(buf);
			j += var_size;
		}
		i++;
	}
}