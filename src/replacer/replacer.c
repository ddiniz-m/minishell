/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:55:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/24 15:49:13 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**var_split(char *str);
char	*add_quotes(char *str, char c);
char	*remove_quotes(char *str, char c);
char	*var_iter(t_list **env, char *var);
char	*double_single(char *str, t_list **env);

//Takes str without quotes, removes anything else that needs removing and calls
//	var_iter to compare str with env variables.
char	*replace_str(char *str, t_list **env, int flag)
{
	char	*buf1;
	char	*buf2;

	buf2 = NULL;
	buf1 = ft_strdup(str);
	if (!buf1)
		return (buf1);
	if (strchr_malloc(buf1, '$') && flag == 0)
		buf2 = replacer(buf1, env, flag);
	else if (flag == 1)
		buf2 = double_single(buf1, env);
	else
		buf2 = var_iter(env, buf1);
	free(buf1);
	if (!buf2)
		return (NULL);
	return (buf2);
}

char	*replace_cond(char *str, char *buf1, t_list **env, int flag)
{
	char	*res;
	
	res = NULL;
	if (str[0] == '$')
		res = replace_dollar(str, buf1, env);
	else if (str[0] == '\"' || (str[0] == '\'' && flag == 0))
		res = replace_quotes(str, buf1, env);
	else
		res = ft_strjoin(buf1, str);
	return (res);
}

//Joins all substituted strings from the split str
char	*replacer(char *str, t_list **env, int flag)
{
	int		i;
	char	*res;
	char	*buf1;
	char	**arr;

	i = 0;
	res = NULL;
	arr = var_split(str);
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		buf1 = ft_strdup(res);
		free(res);
		if (ft_strcmp(arr[i], "$") == 0 && arr[i + 1] 
			&& meta_char(arr[i + 1][0]) != 3 && arr[i + 1][0] != '?')
			res = NULL;
		else
			res = replace_cond(arr[i], buf1, env, flag);
		free(buf1);
		i++;
	}
	free_array(arr);
	return (res);
}

/* If $ is encountered in the array, it replaces the variable with its value
E.g.:
array         new_array
echo   ---->  echo
$HOME  ---->  /ddiniz/home
$VAR   ---->  value */
void	env_var(t_minishell *ms, t_list **env, char **arr)
{
	int		i;
	char	*buf;

	i = 0;
	while (i < arr_size(arr))
	{
		if (strchr_malloc(arr[i], '$'))
		{
			buf = ft_strdup(arr[i]);
			free(arr[i]);
			arr[i] = replacer(buf, env, 0);
			if (!arr[i])
				malloc_error(ms);
			free(buf);
		}
		i++;
	}
}
