/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:57:08 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/04 17:17:09 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	malloc_error(t_var *var)
{
	write(2, "Error: Malloc failed\n", 22);
	free_var(var);
	// Must stop current process and change EXIT_STATUS
}

int	quote_error(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (meta_char(str[i]) == 3)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
			{
				write(1, "MiniShell: Syntax error: Unclosed quote marks\n", 46);
				return (1); // I think it should change exit status
			}
		}
		i++;
	}
	return(0);
}
