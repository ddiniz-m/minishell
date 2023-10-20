/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utl2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:36:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/20 17:25:03 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_quotes(char *str, int i)
{
	if (str[i] && str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
	}
	else if (str[i] && str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
	}
	return (i);
}

int	skip_quotes_rev(char *str, int size)
{
	if (str[size] && str[size] == '\'')
	{
		size--;
		while (str[size] && str[size] != '\'')
			size--;
	}
	else if (str[size] && str[size] == '\"')
	{
		size--;
		while (str[size] && str[size] != '\"')
			size--;
	}
	return (size);
}

//Removes quotes from str. Used for case echo "'$HOME'"
char	*remove_quotes(char *str, char c)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	while (str[i++])
		i = skip_quotes(str, i);
	buf = calloc(sizeof(char), i);
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != c)
			buf[j++] = str[i++];
		if (str[i] && str[i] == c)
			i++;
	}
	return (buf);
}

char	*add_quotes(char *str, char c)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	buf = calloc(sizeof(char), ft_strlen(str) + 3);
	buf[j++] = c;
	while (str[i])
		buf[j++] = str[i++];
	buf[j] = c;
	return (buf);
}

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
