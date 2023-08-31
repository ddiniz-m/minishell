/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:28:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/08/31 18:14:21 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//	Need to figure out how to stop the whole proccess
//	Need to simplify or split into multiple functions
//	Need a separate function to check if the quotation marks are closed or empty
int	str_words_quotes(t_var *var, char *str, char c, int i)
{
	if (str[i] && str[i] == c)
	{
		i++;
		if (str[i] && str[i] == c)
			return (i + 1);
		if (!str[i])
		{
			write(1, "Syntax Error: unclosed quotes\n", 31);
			return (i);
			// Should stop the process
		}
		while (str[i] && (!meta_char(str[i]) || meta_char(str[i]) != c))
		{
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
			{
				write(1, "Syntax Error: unclosed quotes\n", 31);
				break ;
				// Should stop the process
			}
			i++;
			while (str[i] && (!meta_char(str[i]) || str[i] == '$'))
				i++;
			if (str[i] && meta_char(str[i]) == 3)
				c = str[i++];
			else
			{
				var->words++;
				break ;
			}
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

// Maybe should make a separate function just for ($)
/*
Error:
	in the case ($VAR""), it doesn't see any words
*/
int	str_words_others(t_var *var, char *str, int i)
{
	if (str[i] == '$')
	{
		i++;
		var->words++;
		while (str[i] && meta_char(str[i]) == 0)
			i++;
		if (str[i] && meta_char(str[i]) == 3)
		{
			i = str_words_quotes(var, str, str[i], i);
			var->words--;
		}
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
/*
Error:
	in the case (a"") the function doesn't see any words, maybe make a function 	
*/
void	str_words(t_var *var, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		i = str_words_redirect(var, str, i);
		i = str_words_others(var, str, i);
		if (str[i] && meta_char(str[i]) == 3)
			i = str_words_quotes(var, str, str[i], i);
		if (str[i] && !meta_char(str[i]))
		{
			var->words++;
			while (str[i] && !meta_char(str[i]))
				i++;
			if (str[i] && str[i] == '$')
			{
				var->words--;
				if (str[i + 1] && meta_char(str[i + 1]) == 3)
					var->words--;
			}
			else if (str[i] && meta_char(str[i]) == 3)
				var->words--;
		}
	}
}

// Return 0 if regular char;
// Return 1 if space or tab;
// Return 2 if any other meta character;
// Return 3 if quotation mark;
// ------------------ ATTENTION --------------------------
// We might have to separate ($) from the other meta-characters (> < |)
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
