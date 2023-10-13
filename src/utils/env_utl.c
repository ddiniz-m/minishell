/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
<<<<<<< HEAD:src/utils/str_utils.c
/*   Updated: 2023/10/12 13:11:00 by ddiniz-m         ###   ########.fr       */
=======
/*   Updated: 2023/10/12 16:58:45 by mortins-         ###   ########.fr       */
>>>>>>> martim-branch/WudDoo-exit_cd_fixpipes:src/utils/env_utl.c
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
			if (ft_strlen(arr[i]) == 1 || (ft_strlen(arr[i]) == 2 && arr[i][1] == '?'))
				return ;
			buf = env_var_str(arr[i], env);
			free(arr[i]);
			arr[i] = ft_strdup(buf);
			free(buf);
		}
		i++;
	}
}

char	*path_str(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp->data)
	{
		if (ft_strncmp((char *)tmp->data, "PATH=", 5) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->data);
}
