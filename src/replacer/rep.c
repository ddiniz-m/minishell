/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:37:02 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/04 13:59:02 by ddiniz-m         ###   ########.fr       */
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
	int		pre_size;
	int		var_size;
	int		buf_size;
	
	char	*pre;
	char	*var;
	char	*replaced_var;
	char	*buf;
	
	i = 0;
	buf = NULL;
	pre_size = 0;
	buf_size = 0;
	var_size = 0;
	size = ft_strlen(ms->str);
	buf = ft_strdup(ms->str);
/* 	while (i < size)
	{ */
		pre_size = strlen_chr(ms->str, '$');
		pre = malloc(sizeof(char) * (pre_size + 1));
		ft_strlcpy(pre, ms->str, pre_size + 1);

		var_size = 0;
		var_size = var_len(ms->str + pre_size + 1) + 1;
		var = malloc(sizeof(char) * (var_size + 1));
		ft_strlcpy(var, ms->str + pre_size, var_size + 1);

		replaced_var = var_iter(ms->env, var + 1);
		free(var);

		buf = ft_strjoin(pre, replaced_var);
		buf_size = ft_strlen(buf) + 1;
		free(replaced_var);
		
		printf("JOIN: %s\n\n", buf);
		free(buf);
		/* i += buf_size; */
}