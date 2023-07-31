/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:28:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/07/31 18:11:45 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// In the future this function will have to interpretopen quotes
int	str_words_quotes(t_var *var, char *str, char c, int i)
{
	if (str[i] && str[i] == c)
	{
		i++;
		if (str[i] && str[i] != c)
			var->words++;
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

int	str_words_redirect(t_var *var, char *str, int i)
{
	if (str[i] == '>')
	{
		var->words++;
		while (str[i] && str[i] == '>')
			i++;
	}
	else if (str[i] == '<')
	{
		var->words++;
		while (str[i] && str[i] == '<')
			i++;
	}
	return (i);
}

int	str_words_others(t_var *var, char *str, int i)
{
	if (str[i] == '$')
	{
		i++;
		var->words++;
		while (str[i] && meta_char(str[i]) == 0)
			i++;
	}
	else if (str[i] && str[i] == '|')
	{
		var->words++;
		i++;
	}
	else if (str[i] && meta_char(str[i]) == 1)
	{
		while (str[i] && meta_char(str[i]) == 1)
			i++;
	}
	return (i);
}

// how many words are in str
void	str_words(t_var *var, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		i = str_words_quotes(var, str, '\'', i);
		i = str_words_quotes(var, str, '\"', i);
		i = str_words_redirect(var, str, i);
		i = str_words_others(var, str, i);
		if (str[i] && (meta_char(str[i]) == 0))
		{
			var->words++;
			while (str[i] && (meta_char(str[i]) == 0))
				i++;
			if (str[i] && str[i] == '$')
			{
				var->words--;
				if (str[i + 1] && meta_char(str[i + 1]) == 3)
					var->words--;
			}
			else if ((str[i] && (meta_char(str[i]) == 3)))
				var->words--;
		}
	}
}

// Return 0 if regular char;
// Return 1 if space or tab;
// Return 2 if any other meta character;
int	meta_char(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '$' || c == '>' || c == '<' || c == '|')
		return (2);
	if (c == '\'' || c == '\"')
		return (3);
	return (0);
}

//Compares strings until s1 reaches c
int	strchrcmp(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && s2[i] != c)
		i++;
	return (s1[i] - s2[i]);
}