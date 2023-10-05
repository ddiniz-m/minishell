/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:57:08 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/05 16:24:00 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Checks for unclosed quote marks
int	quote_error(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str && str[i])
	{
		if (meta_char(str[i]) == 3)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
			{
				write(2, "MiniShell: syntax error: unclosed quote marks\n", 46);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	pipe_error(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] && meta_char(str[i]) == 3)
			i = str_quotes(str, str[i], i);
		else if (str[i] && str[i] == '|')
		{
			i++;
			while (str[i] && meta_char(str[i]) == 1)
				i++;
			if (str[i] && str[i] == '|')
				return (token_message('|'));
		}
		else
			i++;
	}
	return (0);
}

int	dollar_error(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				break ;
			i++;
		}
		else if (str[i] == '$' && str[i + 1] == '$')
			return (token_message('$'));
		else
			i++;
	}
	return (0);
}

int	token_message(char token)
{
	int	fd;
	/* write(2,"MiniShell: syntax error near unexpected token", 45);
	write(2, " \'", 2);
	write(2, &c, 1);
	write(2, "\'", 1);
	write(2, "\n", 1); */
	fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("MiniShell: syntax error near unexpected token '%c'\n", token);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

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
