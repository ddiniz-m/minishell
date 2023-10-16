/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/16 12:19:19 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* int	n_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if (str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

// To deal with echo "$HOME"aaa, I can't use strtrim.
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	buf = calloc(sizeof(char), ft_strlen(str) - n_quotes(str) + 1);
	while (str[i])
	{
		while (str[i] == '\"')
			i++;
		while (str[i] && str[i] != '\"')
		{
			buf[j] = str[i];
			j++;
			i++;
		}
	}
	return (buf);
} */

// Cases where there is stuff attached to var (aaaaa$HOMEaaa and "$HOME")
char	*chr_var(char *str)
{
	int		i;
	int		size;
	char	*buf1;

	i = 0;
	if (strlen_chr(str, '$') < strlen_chr(str, '\"'))
		size = strlen_chr(str, '$');
	else
		size = strlen_chr(str, '\"');
	printf("SIZE = %i\n", size + 1);
	buf1 = ft_calloc(sizeof(char), size + 1);
	while (str[i] && str[i] != '$' && str[i] != '\"')
	{
		buf1[i] = str[i];
		i++;
	}
	return (buf1);
}

// Cases where $ is called simply (no asdasd$HOMEasd nor "$HOME")
char	*quote_var(char *str)
{
	int		i;
	char	*buf1;
	char	*buf2;

	i = 0;
	buf1 = ft_strdup(str);
	if (str[i] == '\"')
	{
		
	}
	buf2 = str_front_trim(buf1, "$");
	free(buf1);
	return (buf2);
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
	
	if (strcmp_chr(env, var, '=') == 0 && strcmp_chr(var, env, '=') == 0)
	{
		buf1 = str_front_trim(env, var);
		printf("var_cmp buf1 = %s\n", buf1);
		buf2 = str_front_trim(buf1, "=");
		printf("var_cmp buf2 = %s\n", buf2);
		free(buf1);
		if (trim)
		{
			buf1 = ft_strjoin(trim, buf2);
			printf("var_cmp buf1 = %s\n", buf1);
			free(buf2);
			return (buf1);
		}
		printf("var_cmp buf2 = %s\n", buf2);
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
		{
			printf("buf = %s\n", buf);
			return (buf);
		}
		tmp = tmp->next;
		free(buf);
	}
	return (NULL);
}

char	*env_var_str(char *str, t_list **env)
{
	int		i;
	char	*buf1;
	char	*buf2;
	char	*buf3;
	t_list	*tmp;

	i = 0;
	tmp = *env;
	buf2 = NULL;
	printf("STR = %s\n", str);
	if (str[i] != '$' && str[i] != '\"')
	{
		buf1 = chr_var(str);
		printf("chr buf1 = %s\n", buf1);
		buf3 = str_front_trim(str, buf1);
		buf2 = str_front_trim(buf3, "$");
		free(buf3);
		printf("chr buf2 = %s\n", buf2);
		buf3 = var_iter(env, buf1, buf2);
		free(buf1);
		free(buf2);
		if (buf3)
			return(buf3);
	}
	else
	{
		buf1 = quote_var(str);
		printf("quote buf1 = %s\n", buf1);
		buf2 = var_iter(env, NULL, buf1);
		free(buf1);
		if (buf2)
			return(buf2);
	}
	return (NULL);
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
	int		j;
	int		size;
	char	*buf;

	i = 0;
	size = arr_size(arr);
	while (i < size)
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
				if (ft_strcmp(arr[i], "$?") == 0)
					break ;
				buf = env_var_str(arr[i], env);
				printf("Var Value: %s\n", buf);
				if (!buf)
					break ;
				free(arr[i]);
				arr[i] = ft_strdup(buf);
				free(buf);
				break ;
			}
			j++;
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
