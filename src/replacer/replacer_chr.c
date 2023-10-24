/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:25:12 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/24 16:00:41 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*replace_quotes2(char *str, char *buf, t_list **env, int flag)
{
	char	*buf1;
	char	*res;

	buf1 = replace_str(str, env, flag);
	if (buf1[0] == '\'')
		str = add_quotes(buf1, '\"');
	else
		str = ft_strdup(buf1);
	free(buf1);
	res = ft_strjoin(buf, str);
	free(str);
	return (res);
}

char	*str_add_quotes(char *str, char *buf)
{
	char	*res;
	char	*buf1;
	char	*buf2;

	buf1 = add_quotes(str, '\'');
	buf2 = add_quotes(buf1, '\"');
	free(buf1);
	res = ft_strjoin(buf, buf2);
	free(buf2);
	return (res);
}

char	*replace_quotes(char *str, char *buf, t_list **env)
{
	int		flag;
	char	*res;
	char	*buf1;

	flag = 1;
	buf1 = NULL;
	if (str[0] && str[0] == '\"')
	{
		buf1 = remove_quotes(str, '\"');
		flag = 0;
	}
	if (str[0] && str[0] == '\'' && flag == 1)
		buf1 = remove_quotes(str, '\'');
	if (strchr_malloc(buf1, '$') == 0)
	{
		res = str_add_quotes(buf1, buf);
		free(buf1);
		return (res);
	}
	res = replace_quotes2(buf1, buf, env, flag);
	free(buf1);
	return (res);
}

char	*replace_dollar(char *str, char *buf, t_list **env)
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
	if ((str[1] && !ft_isalnum(str[1]) && str[1] != '_' && str[1] != '\\' && \
		str[1] != '\'') || str[1] == '?')
	{
		res = ft_strjoin(buf, str);
		return (res);
	}
	buf1 = ft_strtrim(str, "$");
	buf2 = replace_str(buf1, env, 0);
	res = ft_strjoin(buf, buf2);
	free(buf1);
	free(buf2);
	return (res);
}