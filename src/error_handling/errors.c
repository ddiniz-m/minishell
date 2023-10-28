/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:57:08 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/12 17:09:54 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	syntax_error(t_minishell *ms)
{
	if (quote_error(ms->str) || pipe_error(ms->str) || begin_error(ms->str) || \
		end_of_string_error(ms->str) || double_redir_error(ms->str, '<') || \
		double_redir_error(ms->str, '>') || dollar_error(ms->str) || \
		sucession_error(ms->str) || redir_error(ms->str))
	{
		free(ms->prompt);
		free(ms->str);
		g_exit = 2;
		return (1);
	}
	return (0);
}

void	malloc_error(t_minishell *ms)
{
	write(2, "Error: Malloc failed\n", 22);
	g_exit = 12;
	free_ms(ms);
}

void	open_error(char	*filename)
{
	write(STDERR_FILENO, "Minishell: ", 11);
	g_exit = errno;
	perror(filename);
	//does perror exit the shell lmao?
}
