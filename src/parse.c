/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/19 16:12:34 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parse_main(t_var *var, char *str)
{
	int		i;
	char	**buf;

	i = 0;
	printf("Number of words = %i\n", var->words);
	printf("------------------------------------MAIN STR ARRAY------------------------------------\n");
	buf = split_main(var, str);
	arr_print("MAIN ARRAY", buf);
	printf("\n");
	if (echo_count(buf, var->words) > 0)
		echo_struct_init(var, buf);
}