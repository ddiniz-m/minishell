/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/12 16:50:19 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*env_var_str(char *str, t_list **env)
{
	char	*buf1;
	char	*buf2;
	t_list	*tmp;

	tmp = *env;
	buf1 = ft_strtrim(str, "$");
	while (tmp)
	{
		if (strcmp_chr(buf1, (char *)tmp->data, '=') == 0)
		{
			buf2 = ft_strtrim(tmp->data, buf1);
			free(buf1);
			buf1 = ft_strtrim(buf2, "=");
			str = ft_strdup(buf1);
			return (str);
		}
		tmp = tmp->next;
	}
	return (str);
}

void	env_var(t_list **env, char **arr)
{
	int		i;
	int		size;
	char	*buf;

	i = 0;
	size = arr_size(arr);
	while (i < size)
	{
		if (arr[i][0] == '$')
		{
			buf = env_var_str(arr[i], env);
			free(arr[i]);
			arr[i] = ft_strdup(buf);
		}
		i++;
	}
}
