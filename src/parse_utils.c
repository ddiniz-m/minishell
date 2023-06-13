/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:31:51 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/07 16:56:221 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// how many words are in str
int	str_words(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			if (str[i] && meta_char(str[i]) != 1 && str[i] != '\'')
				words++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			if (str[i] && meta_char(str[i]) != 1 && str[i] != '\"')
				words++;
			while (str[i] && str[i] != '\"')
				i++;
			i++;
		}
		else if (meta_char(str[i]) == 0)
		{
			words++;
			while (str[i] && meta_char(str[i]) == 0)
				i++;
		}
		else if (meta_char(str[i]) == 1)
		{
			while (str[i] && meta_char(str[i]) == 1)
				i++;
		}
		else if (meta_char(str[i]) == 2)
		{
			words++;
			while (str[i] && meta_char(str[i]) == 2)
				i++;
		}
	}
	return (words);
}

// how man c are in str
// see if quotes are odd or even
int	n_char(char *str, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == c)
			n++;
		i++;
	}
	return (n);
}

//Return 0 if regular char;
//Return 1 if space or tab;
//Return 2 if any other meta character;
int	meta_char(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '$' || c == '>' || c == '<')
		return (2);
	if (c == '|' || c == '\\' || c == '.')
		return (2);
	return (0);
}

//returns 1 when it finds 2 char c;
//returns 2 if there is 1 char c in the whole str;
int	quote_state(char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != c)
			i++;
		if (str[i++] == c)
			j++;
		if (j == 2)
			return (1);
	}
	if (j == 1)
		return (2);
	return (0);
}