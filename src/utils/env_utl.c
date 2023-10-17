/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/17 15:43:48 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Trims str untils a $ is reached
// Cases where there is stuff attached to var aaaaa$HOMEaaa
char	*str_chr_trim(char *str)
{
	int		i;
	int		size;
	char	*buf1;

	i = 0;
	if (strlen_chr(str, '$') < strlen_chr(str, '\"'))
		size = strlen_chr(str, '$');
	else
		size = strlen_chr(str, '\"');
	buf1 = ft_calloc(sizeof(char), size + 1);
	while (str[i] && str[i] != '$' && str[i] != '\"')
	{
		buf1[i] = str[i];
		i++;
	}
	return (buf1);
}

//Compares env variables with var.
//Returns the value of var if it finds it in env.
// var = HOME
// env: HOME=/nfs/homes/ddiniz-m
// return: /nfs/homes/ddiniz-m
char	*var_cmp(char *env, char *trim, char *var)
{
	char	*buf1;
	char	*buf2;
	
	if (ft_strncmp(var, env, ft_strlen(var)) == 0)
	{
		buf1 = str_front_trim(env, var);
		buf2 = str_front_trim(buf1, "=");
		free(buf1);
		if (trim)
		{
			buf1 = ft_strjoin(trim, buf2);
			free(buf2);
			return (buf1);
		}
		return (buf2);
	}
	return (NULL);
}

char	*var_iter(t_list **env, char *trim, char *var)
{
	char	*buf;
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		buf = var_cmp((char *)tmp->data, trim, var);
		if (buf)
			return (buf);
		tmp = tmp->next;
		free(buf);
	}
	return (NULL);
}

char	*env_var_str(char *str, t_list **env)
{
	char	*buf1;
	char	*buf2;

	buf1 = NULL;
	buf2 = NULL;
	if (!str)
		return (NULL);
	buf1 = ft_strtrim(str, "\"");
	buf2 = str_front_trim(buf1, "$");
	free(buf1);
	buf1 = var_iter(env, NULL, buf2);
	free(buf2);
	return (buf1);
}

char	*var_sub(char *str, t_list **env)
{
	char	*buf;

	if (!str)
		return (NULL);
	if (ft_strcmp(str, "$?") == 0)
		return (NULL);
	buf = env_var_str(str, env);
	if (!buf)
		return (NULL);
	return (buf);
}

int		var_split_size(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count++;
		if (str[i] != '\"' && str[i] != '$' && str[i] != '\'')
			while (str[i] && str[i] != '\"' && str[i] != '$' && str[i] != '\'')
				i++;
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		else if (str[i] == '$')
		{
			i++;
			while (str[i] && str[i] != '\"' && str[i] != '$' && str[i] != '\'')
				i++;
		}
	}
	return (count);
}

int	var_split_word_size(char *str, int prev)
{
	int	i;

	i = prev;
	if (str[i] != '\"' && str[i] != '$' && str[i] != '\'')
		while (str[i] && str[i] != '\"' && str[i] != '$' && str[i] != '\'')
			i++;
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '$')
	{
		i++;
		while (str[i] && str[i] != '\"' && str[i] != '$' && str[i] != '\'')
			i++;
	}
	return (i - prev);
}

char	*var_split_temp(t_minishell *ms, char *str, int word_len, int pos)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (word_len + 1));
	if (!temp)
		malloc_error(ms);
	while (str[pos] && i < word_len)
		temp[i++] = str[pos++];
	temp[i] = '\0';
	return (temp);
}


char	**var_split(t_minishell *ms, char *str)
{
	int		i;
	int		pos;
	int		size;
	char	**buff;
	int		word_len;

	i = 0;
	pos = 0;
	word_len = 0;
	size = var_split_size(str);
	buff = malloc(sizeof(char *) * (size + 1));
	if (!buff)
		malloc_error(ms);
	while (i < size)
	{
		word_len = var_split_word_size(str, pos);
		buff[i++] = var_split_temp(ms, str, word_len, pos);
		pos += var_split_word_size(str, pos);
	}
	buff[i] = 0;
	return (buff);
}

/* char	*var_sub_dollar(char *res, char *str, t_list **env)
{
	char	*buf1;
	char	*buf2;
	buf2 = var_sub(str, env);
	free(str);
	buf1 = ft_strdup(res);
	free(res);
	res = ft_strjoin(buf1, buf2);
	if (buf2)
		free(buf2);
	free(buf1);
	return (res)
} */

char	*var_sub_join(t_minishell *ms, char *str, t_list **env)
{
	int		i;
	char	*res;
	char	*buf1;
	char	*buf2;
	char	**arr;

	i = 0;
	res = NULL;
	buf2 = NULL;
	arr = var_split(ms, str);
	arr_print("arr", arr);
	free(str);
	while (arr[i])
	{
		buf1 = ft_strdup(res);
		free(res);
		if (ft_strchr(arr[i],'$'))
		{
			buf2 = var_sub(arr[i], env);
			res = ft_strjoin(buf1, buf2);
			if (buf2)
				free(buf2);
		}
		else
			res = ft_strjoin(buf1, arr[i]);
		free(arr[i]);
		free(buf1);
		i++;
	}
	free(arr);
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
	int		j;

	i = 0;
	while (i < arr_size(arr))
	{
		j = 0;
		while (j < (int)ft_strlen(arr[i]))
		{
			if (arr[i][j] == '\'')
			{
				j++;
				continue ;
			}
			if (arr[i][j] == '$')
			{
				arr[i] = var_sub_join(ms, arr[i], env);
				break ;
			}
			j++;
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
