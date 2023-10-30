/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:57:08 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/30 16:30:46 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	syntax_error(t_minishell *ms)
{
	if (quote_syntax(ms->str) || pipe_syntax(ms->str) || start_syntax(ms->str) \
		|| end_syntax(ms->str) || redir_syntax(ms->str) \
		|| double_redir_syntax(ms->str) || dollar_syntax(ms->str) \
		|| sucession_syntax(ms->str))
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
