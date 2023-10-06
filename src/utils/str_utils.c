/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/06 16:15:03 by ddiniz-m         ###   ########.fr       */
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
			free(buf1);
			free(buf2);
			return (str);
		}
		tmp = tmp->next;
	}
	free(buf1);
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
			free(buf);
		}
		i++;
	}
}
