/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:02:32 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/22 16:49:30 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	split_word_len_quotes(char *str, int i, char c)
{
	if (str[i] == c && str[i])
	{
		i++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i])
			i++;
		if (str[i] && meta_char(str[i]) == 0)
		{
			while (str[i] && meta_char(str[i]) == 0)
				i++;
		}
	}
	return (i);
}

int	split_word_len_redirect(char *str, int i)
{
	if (str[i] == '>')
	{
		while (str[i] && str[i] == '>')
			i++;
	}
	else if (str[i] == '<')
	{
		while (str[i] && str[i] == '<')
			i++;
	}
	return (i);
}

// size of str until next specific character
int	split_word_len(char *str)
{
	int	i;

	i = split_word_len_quotes(str, 0, '\'');
	i = split_word_len_quotes(str, i, '\"');
	i = split_word_len_redirect(str, i);
	if (i > 0)
		return (i);
	if (str[i] && meta_char(str[i]) == 0)
	{
		while (str[i] && meta_char(str[i]) == 0)
			i++;
	}
	else if (str[i] == '$' && str[i++])
	{
		while (str[i] && meta_char(str[i]) == 0)
			i++;
	}
	else if (str[i] && str[i] == '|')
		i++;
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
	while (*str && i < word_len)
		temp[i++] = *str++;
	temp[i] = '\0';
	return (temp);
}

// splits str
char	**split_main(t_var *var, char *str)
{
	int		i;
	int		word_len;
	char	**buff;

	i = 0;
	printf("Words = %d\n", var->words);
	buff = malloc(sizeof(char *) * (var->words + 1));
	if (!buff)
		return (NULL);
	while (i < var->words)
	{
		while (*str && meta_char(*str) == 1)
			str++;
		word_len = split_word_len(str);
		buff[i++] = split_temp(str, word_len);
		str = str + word_len;
	}
	buff[i] = 0;
	return (buff);
}
