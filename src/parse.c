/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/13 18:20:35 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parse_main(char *str)
{
	int		i;
	int		words;
	char	**arr;
	char	**echo;

	i = 0;
	printf("Number of words = %i\n", words);
	
	printf("------------------------------------MAIN STR ARRAY------------------------------------\n");
	arr = split(str, words);
	while(i < words)
		printf("%s\n", arr[i++]);
	
	echo = echo_join_words(arr, words);
	i = 0;
	if (echo)
	{
		printf("------------------------------------ECHO ARRAY------------------------------------\n");
		while(echo[i])
			printf("%s\n", echo[i++]);
	}
}