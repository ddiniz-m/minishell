/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:45:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/05 17:20:49 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Error:
	-Should give syntax error if quotes are unclosed
	-Splits ("""a") into ("), instead of ("a") <---- temporarily fixed to ("""a")
*/
int	split_quotes(char *str, char c, int i)
{
	int	a;

	a = 0;
	if (str[i] && str[i] == c)
	{
		i++;
		if (str[i] && str[i] == c)
			return (split_empty_quotes(str, i + 1));
		while (str[i] && str[i] != c)
			i++;
		if (!str[i])
			return (i);	// Should stop the process
		i++;
		if (str[i] && !meta_char(str[i]))
			return (str_words_plain(str, i));
		else if (str[i] && str[i] == '$')
			return (str_words_envar(str, i));
		else if (str[i] && meta_char(str[i]) == 3)
			return (split_quotes(str, str[i], i));
	}
	return (i);
}

int	split_empty_quotes(char *str, int i)
{
	if (str[i] && !meta_char(str[i]))
		return (str_words_plain(str, i));
	else if (str[i] && str[i] == '$')
		return (str_words_envar(str, i));
	else if (str[i] && meta_char(str[i]) == 3)
		return (split_quotes(str, str[i], i));
	else
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
		return (split_quotes(str, str[i], i));
	if (str[i] && meta_char(str[i]) == 2)
		return (str_words_others(str, i));
	if (str[i] && str[i] == '$')
		return (str_words_envar(str, i));
	if (str[i] && !meta_char(str[i]))
		return (str_words_plain(str, i));
	return (i);
}
