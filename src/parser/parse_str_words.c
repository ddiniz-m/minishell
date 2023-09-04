/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:28:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/04 14:18:02 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//	Need to figure out how to stop the whole proccess
//	Need to simplify or split into multiple functions
//	Need a separate function to check if there are unclosed quote marks
/*	Errors:
	Interprets ("a""""c") as unclosed quotes instead of ("a""c")
	^^ might be fine cause this is just a word counter ^^
*/
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
		while (str[i] && (!meta_char(str[i]) || str[i] != c))
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
			if (!str[i] || meta_char(str[i]) != 3)
			{
				var->words++;
				break ;
			}
			while (str[i] && meta_char(str[i]) == 3)
			{
				if (str[i] && meta_char(str[i]) == 3)
					c = str[i++];
				if (str[i] && str[i] == c)
					i++;
			}
		}
	}
	return (i);
}

int	str_words_envar(t_var *var, char *str, int i)
{
	int	a;

	if (str[i] == '$')
	{
		while (str[i] == '$')
			i++;
		var->words++;
		a = var->words;
		if (str[i] && (!meta_char(str[i]) || meta_char(str[i]) == 3))
		{
			while (str[i] && !meta_char(str[i]))
				i++;
			if (str[i] && (!meta_char(str[i]) || meta_char(str[i]) == 3))
				i = str_words_quotes(var, str, str[i], i);
			if (a < var->words)
				var->words--;
		}
		else
		{
			while (str[i] && !meta_char(str[i]))
				i++;
		}
	}
	return (i);
}

int	str_words_others(t_var *var, char *str, int i)
{
	if (str[i] && meta_char(str[i]) == 1)
	{
		while (str[i] && meta_char(str[i]) == 1)
			i++;
	}
	else if (str[i] && str[i] == '|')
	{
		var->words++;
		i++;
	}
	else if (str[i] == '>')
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
