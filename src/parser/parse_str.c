/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:26:00 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/05 17:29:07 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// how many words are in str
void	str_words(t_var *var, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		while (str[i] && meta_char(str[i]) == 1)
			i++;
		if (str[i] && meta_char(str[i]) != 1 && meta_char(str[i]) != 3)
			var->words++;
		if (str[i] && meta_char(str[i]) == 2)
			i = str_words_others(str, i);
		else if (str[i] && meta_char(str[i]) == 3)
			i = str_words_quotes(var, str, str[i], i);
		else if (str[i] && str[i] == '$')
			i = str_words_envar(str, i);
		else if (str[i] && !meta_char(str[i]))
			i = str_words_plain(str, i);
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
		return(4); // currently only used to distinguish between '$' and regular chars
	return (0);
}
