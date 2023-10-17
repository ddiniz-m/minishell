/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/17 14:11:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//replaces `str` by its value (`str` would be something like "$HOME")
char	*env_var_str(char *str, t_list **env)
{
	char	*buf1;
	char	*buf2;
	//char	*new_str;
	t_list	*tmp;

	tmp = *env;
	buf1 = ft_strtrim(str, "$");
	while (tmp)
	{
		if (strcmp_nochr(buf1, (char *)tmp->data, '=') == 0)
		{
			buf2 = ft_strtrim(tmp->data, buf1);
			free(buf1);
			buf1 = ft_strtrim(buf2, "=");
			free(buf2);
			str = ft_strdup(buf1);
			free(buf1);
			return (str);
		}
		tmp = tmp->next;
	}
	free(buf1);
	return (str);
}

// reads main_arr and replaces all environment variables by their values
void	env_var(t_list **env, char **arr)
{
	int		i;
	char	*buf;

	i = 0;
	while (i < arr_size(arr))
	{
		if (arr[i][0] == '$')
		{
			buf = env_var_str(arr[i], env);
			free(arr[i]);
			arr[i] = buf;
		}
		i++;
	}
}

// equivalent to `env | grep var`
char	*var_str(t_list *env, char *var)
{
	t_list	*tmp;

	tmp = env;
	while (tmp->data)
	{
		if (ft_strncmp((char *)tmp->data, var, ft_strlen(var)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->data);
}
