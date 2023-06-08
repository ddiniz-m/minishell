/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/08 18:15:53 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*parse_main(char *str)
{
	int		i;
	int		words;
	char	**buf;

	i = 0;
	printf("Number of words = %i\n", words);
	printf("Number of double quotes = %i\n", n_char(str, '\"'));
	printf("Number of single quotes = %i\n", n_char(str, '\''));
	printf("None(0)/Closed(1)/Open(2) Double Quotes = %i\n", quote_state(str, '\"'));
	printf("None(0)/Closed(1)/Open(2) Single Quotes = %i\n", quote_state(str, '\''));
	buf = split(str);
	while(i < words)
	{
		printf("%s\n", buf[i++]);
	}
	return (str);
}