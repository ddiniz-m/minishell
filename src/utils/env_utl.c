/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/18 17:51:26 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_quotes(char *str, int i);

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
char	*var_cmp(char *env, char *var)
{
	char	*buf1;
	char	*buf2;
	
	if (strcmp_nochr(var, env, '=') == 0)
	{
		buf1 = str_front_trim(env, var);
		buf2 = str_front_trim(buf1, "=");
		free(buf1);
		return (buf2);
	}
	return (NULL);
}

char	*var_iter(t_list **env, char *var)
{
	char	*buf;
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		buf = var_cmp((char *)tmp->data, var);
		if (buf)
			return (buf);
		tmp = tmp->next;
		free(buf);
	}
	return (NULL);
}


char	*var_sub_join(t_minishell *ms, char *str, t_list **env);

char	*env_var_str(t_minishell *ms, char *buf, t_list **env)
{
	char	*buf2;

	buf2 = NULL;
	if (buf[0] != '$')
	{
		buf2 = var_sub_join(ms, buf, env);
		buf = str_front_trim(buf2, "$");
		free(buf2);
		return (buf);
	}
	else
	{
		buf2 = str_front_trim(buf, "$");
		if (meta_char(buf2[0]) == 5 || meta_char(buf2[0]) == 2
			|| meta_char(buf2[0]) == 3)
		{
			free(buf2);
			return (buf);
		}
		free(buf);
		buf = var_iter(env, buf2);
		free(buf2);
	}
	return (buf);
}

char	*var_sub(t_minishell *ms, char *str, t_list **env)
{
	char	*buf1;
	char	*buf2;

	if (!str)
		return (NULL);
	buf2 = NULL;
	buf1 = ft_strtrim(str, "\"");
	printf("buf1 = %s\n", buf1);
	if (ft_strcmp(buf1, "$") == 0 || ft_strcmp(buf1, "$?") == 0)
		return (buf1);
	buf2 = env_var_str(ms, buf1, env);
	if (!buf2)
		return (NULL);
	return (buf2);
}

//Returns how many "words" it'll split str into
int		var_split_size(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen(str))
	{
		count++;
		if (str[i] && meta_char(str[i]) != 3 && meta_char(str[i]) != 4)
			while (meta_char(str[i]) != 3 && meta_char(str[i]) != 4)
				i++;
		else if ((meta_char(str[i]) == 3))
		{
			i = skip_quotes(str, i);
			i++;
		}
		else if (str[i] == '$')
		{
			i++;
			while (str[i] && meta_char(str[i]) != 3 && meta_char(str[i]) != 4
				&& meta_char(str[i]) != 1)
				i++;
		}
	}
	return (count);
}

//Receives previous position returns lenght of word it started on
int	var_split_word_size(char *str, int prev)
{
	int	i;

	i = prev;
	if (str[i] && meta_char(str[i]) != 3 && meta_char(str[i]) != 4)
		while (str[i] && meta_char(str[i]) != 3 && meta_char(str[i]) != 4)
			i++;
	else if (meta_char(str[i]) == 3)
	{
		i = skip_quotes(str, i);
		i++;
	}
	else if (meta_char(str[i]) == 4 && str[i + 1] && meta_char(str[i + 1]) != 1)
	{
		i++;
		while (str[i] && meta_char(str[i]) != 3 && meta_char(str[i]) != 4)
			i++;
	}
	else
		i++;
	return (i - prev);
}

//Creates each string of the split array
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

//Splits str to be easier to work with
//E.g.: abc"abc$HOME"$PATHb becomes:
// arr0 = abc
// arr1 = "abc$HOME"
// arr2 = $PATHb
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

char	*var_sub_dollar(t_minishell *ms, char *str, char *buf, t_list **env)
{
	char	*buf2;
	char	*res;

	buf2 = NULL;
	buf2 = var_sub(ms, str, env);
	res = ft_strjoin(buf, buf2);
	if (buf2)
		free(buf2);
	return (res);
}

//Joins all substituted strings from the split str
char	*var_sub_join(t_minishell *ms, char *str, t_list **env)
{
	int		i;
	char	*res;
	char	*buf1;
	char	**arr;

	i = 0;
	res = NULL;
	arr = var_split(ms, str);
	//arr_print("arr", arr);
	free(str);
	while (arr[i])
	{
		buf1 = ft_strdup(res);
		free(res);
		if (arr[i][0] == '$' || arr[i][0] == '\"')
		{
			res = var_sub_dollar(ms, arr[i], buf1, env);
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
		printf("arr[i] = %s\n", arr[i]);
		while (j < (int)ft_strlen(arr[i]))
		{
			if (arr[i][j] == '\'')
			{
				j++;
				continue ;
			}
			if (ft_strchr(arr[i], '$'))
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
