/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/19 15:04:20 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*add_quotes(char *str, char c);
int		skip_quotes(char *str, int i);
char	*str_chr_trim(char *str);
int		skip_quotes_rev(char *str, int size);
char	*remove_quotes(char *str, char c);
char	**var_split(t_minishell *ms, char *str);
char	*var_sub_join(t_minishell *ms, char *str, t_list **env);


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

char	*env_var_str(t_minishell *ms, char *buf, t_list **env)
{
	char	*buf2;

	buf2 = NULL;
	if (!buf)
		return (buf);
	if (buf[0] && buf[0] != '$')
	{
		buf2 = var_sub_join(ms, buf, env);
		buf = str_front_trim(buf2, "$");
		return (buf);
	}
	else
	{
		buf2 = str_front_trim(buf, "$");
	/* 	if (meta_char(buf[0]) != 1 && (meta_char(buf[0]) == 2 
			|| !ft_isalnum(buf[0]) || meta_char(buf[0]) == 3))
		{
			printf("env_var buf2 = %s\n", buf2);
			return (buf2);
		} */
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
	/* if (ft_strcmp(buf1, str) != 0 && ft_strchr(buf1, '\''))
	{
		buf2 = remove_quotes(buf1, '\'');
		printf("buf2 = %s\n", buf2);
		buf1 = env_var_str(ms, buf2, env);
		printf("buf1 = %s\n", buf1);
		if (!buf1)
		{
			free(buf2);
			return (NULL);
		}
		return (buf2);
	} */
	if (ft_strcmp(buf1, "$") == 0)
		return (buf1);
	buf2 = env_var_str(ms, buf1, env);
	printf("buf2 = %s\n", buf2);
	if (!buf2)
		return (NULL);
	return (buf2);
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
	arr_print("arr", arr);
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
