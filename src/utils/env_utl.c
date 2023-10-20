/* ***************************************************************************/

/*                                                                           */

/*                                                        :::      ::::::::  */

/*   env_utl.c                                          :+:      :+:    :+:  */

/*                                                    +:+ +:+         +:+    */

/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+       */

/*                                                +#+#+#+#+#+   +#+          */

/*   Created: 2023/10/06 15:14:04 by  ddiniz-m         #+#    #+#            */

/*   Updated: 2023/10/20 11:59:50 by ddiniz-m         ###   ########.fr      */

/*                                                                           */

/* ***************************************************************************/


#include "../../inc/minishell.h"

char	*add_quotes(char *str, char c);
int		skip_quotes(char *str, int i);
char	*str_chr_trim(char *str);
int		skip_quotes_rev(char *str, int size);
char	*remove_quotes(char *str, char c);
char	**var_split(char *str);
char	*var_sub_join(char *str, t_list **env, int flag);


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
	if (strchr_malloc(buf1, '$') || strchr_malloc(buf1, '\'')
		|| strchr_malloc(buf1, '\''))
		buf2 = var_sub_join(buf1, env, flag);
	else
		buf2 = var_iter(env, buf1);
	free(buf1);
	if (!buf2)
		return (NULL);
	return (buf2);
}

char	*var_sub_double_quotes(char *str, char *buf, t_list **env, char c)
{
	char	*res;
	char	*buf1;
	char	*buf2;

	buf1 = remove_quotes(str, c);
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
	if (str[1] && !ft_isalpha(str[1]) && str[1] != '\\' && str[1] != '\'')
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
	//arr_print("arr", arr);
	while (arr[i])
	{
		buf1 = ft_strdup(res);
		free(res);
		if (arr[i][0] == '$')
		{
			res = var_sub_dollar(arr[i], buf1, env);
		}
		else if (arr[i][0] == '\"')
		{
			res = var_sub_double_quotes(arr[i], buf1, env, '\"');
		}
		else if (arr[i][0] == '\'' && flag == 1)
		{
			res = var_sub_double_quotes(arr[i], buf1, env, '\'');
		}
		else
		{
			res = ft_strjoin(buf1, arr[i]);
		}
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
