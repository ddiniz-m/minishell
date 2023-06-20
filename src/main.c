/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/20 18:43:46 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(void)
{
	char	*str;

	signal_init();
	while (1)
	{
		str = readline("Minishell >$ ");
		add_history(str);
		signal_exit(str);
		if (str[0] == 'c' && str[1] == 'd' && str[2] == ' ')
		{
			if (str[3] == 'a')
				cd(NULL);
			else
				cd(str + 3);
		}
		else if (str[0] == 'p' && str[1] == 'w' && str[2] == 'd')
			pwd();
		free(str);
	}
}
