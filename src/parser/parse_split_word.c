/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:45:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/08/31 18:01:54 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Error:
	-Should give syntax error if quotes are unclosed
*/
int	split_word_quotes(char *str, char c, int i)
{
	if (str[i] && str[i] == c)
	{
		i++;
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
				break ;
		}
	}
	return (i);
}

int	split_word_redirect(char *str)
{
	int	i;

	i = 0;
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

int	split_word_envar(char *str, int i)
{
	if (str[i] == '$')
	{
		i++;
		while (str[i] && (meta_char(str[i]) == 0 || meta_char(str[i]) == 3))
			i++;
	}
	else if (str[i] && str[i] == '|')
		i++;
	return (i);
}

// size of str until next specific character
/*
	Error:
	in the case (""a), this prints (""a) instead of (a)
	in the case ("" "a"), this prints ("") instead of ("a")
	We need to be able to tell split where to start splitting

	Reminder to figure out where/how we are gonna substitute ($VAR) by its
	actual value
*/
int	split_word(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
		return (split_word_quotes(str, '\'', 0));
	if (str[i] == '\"')
		return (split_word_quotes(str, '\"', 0));
	if (str[i] == '>' || str[i] == '<')
		return (split_word_redirect(str));
	if (str[i] == '|' || str[i] == '$')
		return (split_word_envar(str, 0));
	if (str[i] && (meta_char(str[i]) == 0))
	{
		while (str[i] && (meta_char(str[i]) == 0))
			i++;
		if (str[i] && str[i] == '\'')
			return (split_word_quotes(str, '\'', i));
		else if (str[i] && str[i] == '\"')
			return (split_word_quotes(str, '\"', i));
		else if (str[i] && str[i] == '$')
			return (split_word_envar(str, i));
	}
	return (i);
}
