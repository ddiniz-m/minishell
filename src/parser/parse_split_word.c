/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:45:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/04 14:18:25 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Error:
	-Should give syntax error if quotes are unclosed
	-Splits ("""a") into ("), instead of ("a") <---- temporarily fixed
	-Interprets ("a""""c") as unclosed quotes instead of ("a""c")
*/
int	split_quotes(char *str, char c, int i)
{
	if (str[i] && str[i] == c)
	{
		i++;
		while (str[i] && str[i] == c)   // Temporary fix until we can tell split where to start splitting
			i++;
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
			if (!str[i] || meta_char(str[i]) != 3) // ----> | Temporary fix for not being able to tell split where to split
				break ;
			while (str[i] && meta_char(str[i]) == 3) // --> | Temporary fix for not being able to tell split where to split
			{
				if (str[i] && meta_char(str[i]) == 3) // -> | Temporary fix for not being able to tell split where to split
					c = str[i++];
				if (str[i] && str[i] == c) // ------------> | Temporary fix for not being able to tell split where to split
					i++;
			}
		}
	}
	return (i);
}

int	split_others(char *str)
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
	else if (str[i] && str[i] == '|')
		i++;
	return (i);
}

int	split_envar(char *str, int i)
{
	if (str[i] == '$')
	{
		while (str[i] == '$')
			i++;
		if (str[i] && (!meta_char(str[i]) || meta_char(str[i]) == 3))
		{
			while (str[i] && !meta_char(str[i]))
				i++;
			if (str[i] && (!meta_char(str[i]) || meta_char(str[i]) == 3))
				i = split_quotes(str, str[i], i);
		}
		else
		{
			while (str[i] && !meta_char(str[i]))
				i++;
		}
	}
	return (i);
}

// size of str until next specific character
/*
	Error:
	in the case (""a), this prints (""a) instead of (a)
	in the case ("" "a"), this prints ("") instead of ("a")
	We need to be able to tell split where to start splitting
*/
int	split_word(char *str)
{
	int	i;

	i = 0;
	if (str[i] && meta_char(str[i]) == 3)
		return (split_quotes(str, str[i], 0));
	if (str[i] && meta_char(str[i]) == 2)
		return (split_others(str));
	if (str[i] && str[i] == '$')
		return (split_envar(str, 0));
	if (str[i] && !meta_char(str[i]))
	{
		while (str[i] && !meta_char(str[i]))
			i++;
		if (str[i] && meta_char(str[i]) == 3)
			return (split_quotes(str, str[i], i));
		else if (str[i] && str[i] == '$')
			return (split_envar(str, i));
	}
	return (i);
}
