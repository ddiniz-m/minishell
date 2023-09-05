/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:28:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/05 17:29:26 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	str_words_plain(char *str, int i)
{
	if (str[i] && !meta_char(str[i]))
	{
		while (str[i] && !meta_char(str[i]))
			i++;
		if (str[i] && str[i] == '$')
			return (str_words_envar(str, i));
		else if (str[i] && meta_char(str[i]) == 3)
			return (split_quotes(str, str[i], i));
	}
	return (i);
}

//	Need to figure out how to stop the whole proccess
//	Need to simplify or split into multiple functions
//	Need a separate function to check if there are unclosed quote marks
/*	Errors:
	Interprets ("a""""c") as ("a""""c") instead of ("a""c")
	^^ should be fine cause this is just a word counter ^^
*/
int	str_words_quotes(t_var *var, char *str, char c, int i)
{
	int	words;

	if (str[i] && str[i] == c)
	{
		i++;
		if (str[i] && str[i] == c)
			return (i + 1);
		while (str[i] && str[i] != c)
			i++;
		if (!str[i])
		{
			write(1, "Syntax Error: unclosed quotes\n", 31);
			return (i); // Should stop the process
		}
		var->words++;
		i++;
		if (str[i] && !meta_char(str[i]))
			return (str_words_plain(str, i));
		else if (str[i] && str[i] == '$')
			return (str_words_envar(str, i));
		else if (str[i] && meta_char(str[i]) == 3)
		{
			words = var->words;
			i = split_quotes(str, str[i], i);
			if (words < var->words)
				var->words--;
		}
	}
	return (i);
}

int	str_words_envar(char *str, int i)
{
	if (str[i] == '$')
	{
		while (str[i] == '$')
			i++;
		if (str[i] && meta_char(str[i]) == 3)
			return (split_quotes(str, str[i], i));
		else if (str[i] && !meta_char(str[i]))
			return (str_words_plain(str, i));
	}
	return (i);
}

int	str_words_others(char *str, int i)
{
	if (str[i] && str[i] == '|')
		i++;
	else if (str[i] == '>')
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
