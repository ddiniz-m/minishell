/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:55:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/23 14:26:51 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**var_split(char *str);
char	*add_quotes(char *str, char c);
char	*remove_quotes(char *str, char c);
char	*var_iter(t_list **env, char *var);
char	*var_double_single(char *str, t_list **env);
char	*var_sub_join(char *str, t_list **env, int flag);
char	*var_sub_cond(char *str, char *buf1, t_list **env, int flag);

//Takes str without quotes, removes anything else that needs removing and calls
//	var_iter to compare str with env variables.
char	*env_var_str(char *str, t_list **env, int flag)
{
	char	*buf1;
	char	*buf2;

	buf2 = NULL;
	buf1 = ft_strdup(str);
	if (!buf1)
		return (buf1);
	if ((strchr_malloc(buf1, '$') || strchr_malloc(buf1, '\"') 
			|| (strchr_malloc(buf1, '\''))) && flag == 1)
		buf2 = var_sub_join(buf1, env, flag);
	else if ((strchr_malloc(buf1, '\'') && flag == 0))
		buf2 = var_double_single(buf1, env);
	else
		buf2 = var_iter(env, buf1);
	free(buf1);
	if (!buf2)
		return (NULL);
	return (buf2);
}

char	*var_sub_quotes(char *str, char *buf, t_list **env)
{
	char	*res;
	char	*buf1;
	char	*buf2;

	buf1 = NULL;
	if (str[0] && str[0] == '\'')
		buf1 = remove_quotes(str, '\'');
	else if (str[0] && str[0] == '\"')
		buf1 = remove_quotes(str, '\"');
	if (strchr_malloc(buf1, '$') == 0)
	{
		res = ft_strjoin(buf, buf1);
		free(buf1);
		return (res);
	}
	if (buf1[0] && buf1[0] == '\'')
		buf2 = env_var_str(buf1, env, 0);
	else
		buf2 = env_var_str(buf1, env, 1);
	free(buf1);
	buf1 = add_quotes(buf2, '\"');
	res = ft_strjoin(buf, buf1);
	free(buf1);
	free(buf2);
	return (res);
}

char	*var_sub_dollar(char *str, char *buf, t_list **env)
{
	char	*res;
	char	*buf1;
	char	*buf2;

	buf2 = NULL;
	if (ft_strcmp(str, "$") == 0)
	{
		res = ft_strjoin(buf, str);
		return (res);
	}
	if (str[1] && !ft_isalnum(str[1]) && str[1] != '_' && str[1] != '\\' && \
		str[1] != '\'')
	{
		res = ft_strjoin(buf, str);
		return (res);
	}
	buf1 = str_front_trim(str, "$");
	buf2 = env_var_str(buf1, env, 0);
	res = ft_strjoin(buf, buf2);
	free(buf1);
	free(buf2);
	return (res);
}

//Joins all substituted strings from the split str
char	*var_sub_join(char *str, t_list **env, int flag)
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
		if (arr[i][0] && arr[i][0] == '$' && arr[i + 1]
			&& !ft_isalnum(arr[i + 1][0]) && arr[i + 1][0] != '_'
			&& arr[i + 1][0] != '\\' && arr[i + 1][0] != '\'')
			;
		else
			res = var_sub_cond(arr[i], buf1, env, flag);
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
			arr[i] = var_sub_join(buf, env, 0);
			if (!arr[i])
				malloc_error(ms);
			free(buf);
		}
		i++;
	}
}
