/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:31:51 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/06 18:01:48 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	str_words(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while(str && str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
			words++;
		while(str[i] && str[i] != ' ')
			i++;
	}
	return (words);
}
