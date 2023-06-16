/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:02:32 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/16 15:57:56 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// size of str until next specific character
int	split_word_len(char *str)
{
	int	i;

	i = 0;
	if(str[i] && (str[i] == '\''))
	{
		i++;
		while (str[i] && (str[i] != '\''))
			i++;
		i++;
	}
	else if(str[i] && (str[i] == '\"'))
	{
		i++;
		while (str[i] && (str[i] != '\"'))
			i++;
		i++;
		if (str[i] && meta_char(str[i]) != 1)
		{
			while (str[i] && meta_char(str[i]) == 0)
			i++;
		}
	}
	else if(str[i] && meta_char(str[i]) == 0)
	{
		while (str[i] && meta_char(str[i]) == 0)
			i++;
	}
	else if(str[i] && meta_char(str[i]) == 2)
	{
		while (str[i] && meta_char(str[i]) == 2)
			i++;
	}
	return (i);
}

char	*split_temp(char *str, int word_len)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (word_len + 1));
	if (!temp)
		return (NULL);
	while(*str && i < word_len)
		temp[i++] = *str++;
	temp[i] = '\0';
	return (temp);
}

char	**split(t_var *var, char *str)
{
	int		i;
	int		word_len;
	char	**buff;

	i = 0;
	buff = malloc(sizeof(char *) * (var->words + 1));
	if (!buff)
		return (NULL);
	while(i < var->words)
	{
		while (*str && meta_char(*str) == 1)
			str++;
		word_len = split_word_len(str);
		buff[i++] = split_temp(str, word_len);
		str = str + word_len;
	}
	buff[i] = 0;
	return(buff);
}
