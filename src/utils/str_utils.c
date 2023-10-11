/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/11 17:26:12 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//transforms HOME=/ddiniz-m/home into /ddiniz-m
char	*env_var_str(char *str, t_list **env)
{
	char	*buf1;
	char	*buf2;
	t_list	*tmp;
	
	tmp = *env;
	buf1 = ft_strtrim(str, "$");
	while (tmp)
	{
		printf("tmp->data = %s\n",(char *)tmp->data);
		if (strcmp_chr(buf1, (char *)tmp->data, '=') == 0)
		{
			buf2 = ft_strtrim(tmp->data, buf1);
			printf("buf2 = %s\n", buf2);
			free(buf1);
			buf1 = ft_strtrim(buf2, "=");
			printf("buf1 = %s\n", buf1);
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

/* If $ is encountered in the array, it replaces the variable with its value
E.g.:
array         new_array
echo   ---->  echo
$HOME  ---->  /ddiniz/home
$VAR   ---->  value */
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
			printf("buf = %s\n", buf);
			free(arr[i]);
			arr[i] = ft_strdup(buf);
			free(buf);
		}
		i++;
	}
}
