/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:26:00 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/04 14:18:35 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//	Maybe make a separatefunction that checks if there's unclosed quotes

// how many words are in str
// Error:
//	- In the case (a"") the function doesn't see any words, maybe make a
//		function specific for plain text
void	str_words(t_var *var, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] && (meta_char(str[i]) == 1 || meta_char(str[i]) == 2))
			i = str_words_others(var, str, i);
		if (str[i] && meta_char(str[i]) == 3)
			i = str_words_quotes(var, str, str[i], i);
		if (str[i] && str[i] == '$')
			i = str_words_envar(var, str, i);
		if (str[i] && !meta_char(str[i]))
		{
			var->words++;
			while (str[i] && !meta_char(str[i]))
				i++;
			if (str[i] && str[i] == '$')
			{
				i = str_words_envar(var, str, i);
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
// Return 4 if dollar sign;
int	meta_char(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '>' || c == '<' || c == '|')
		return (2);
	if (c == '\'' || c == '\"')
		return (3);
	if (c == '$')
		return (4); // currently not in use anywhere
	return (0);
}
