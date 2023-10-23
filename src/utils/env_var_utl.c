/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:25:15 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/23 14:26:02 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*add_quotes(char *str, char c);
char	*remove_quotes(char *str, char c);
char	*var_sub_dollar(char *str, char *buf, t_list **env);
char	*var_sub_quotes(char *str, char *buf, t_list **env);

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

char	*var_sub_cond(char *str, char *buf1, t_list **env, int flag)
{
	char	*res;
	
	res = NULL;
	if (str[0] == '$')
		res = var_sub_dollar(str, buf1, env);
	else if (str[0] == '\"' || (str[0] == '\'' && flag == 1))
		res = var_sub_quotes(str, buf1, env);
	else
		res = ft_strjoin(buf1, str);
	return (res);
}

//This is only called when there are single quotes inside double quotes.
//Removes quotes, $ and then iters through env, substitues by var value and adds quotes back.
char	*var_double_single(char *str, t_list **env)
{
	char	*buf1;

	buf1 = remove_quotes(str, '\'');
	str = str_front_trim(buf1, "$");
	free(buf1);
	buf1 = var_iter(env, str);
	free(str);
	str = add_quotes(buf1, '\'');
	free(buf1);
	return (str);
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
