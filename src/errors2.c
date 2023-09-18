/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:44:37 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/18 16:13:22 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Checks for metachar at the start of str
int	begin_error(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (str[i] && meta_char(str[i]) == 1)
		i++;
	if (str[i] && str[i] == '|')
		return(token_message(str[i]));
	else if (str[i] && meta_char(str[i]) == 2)
		return (write(2, 
		"MiniShell: syntax error near unexpected token 'newline'", 55));
	return (0);
}

//Checks for metachar at the end of str
int	end_of_string_error(char *str)
{
	int	size;
	
	size = ft_strlen(str);
	while(size >= 0)
	{
		if (meta_char(str[size]) == 2)
		{
			printf("test1\n");
			return (token_message(str[size]));
		}
		
	}
	return (0);
}

// Checks for ><
int	redir_error(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size - 1)
	{
		while (str[i] && str[i] != '<' && str[i] != '>')
			i++;
		if (str[i] && str[i] == '>')
			if (str[++i] == '<')
			{
				printf("test2\n");
				return(token_message(str[i]));
			}
		i++;
	}
	return (0);
}

//Checks for >> |
int	heredoc_error(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size - 1)
	{
		while (i < size && str[i] != '<')
			i++;
		i++;
		if (i < size && str[i] == '<')
			i++;
		while (i < size && meta_char(str[i]) == 1)
			i++;
		if (i < size  && meta_char(str[i]) == 2)
		{
			printf("test3\n");
			return (token_message(str[i]));
		}
		i++;
	}
	return (0);
}

//Checks if there are any >, < or | in sucession (divided by whitespace)
//Example: hello > > world; hello > | world: hello > < world
int	sucession_error(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size - 1)
	{
		while (i < size && str[i] != '<' && str[i] != '>')
			i++;
		i++;
		if (i < size && meta_char(str[i]) == 1)
			while (str[i] && meta_char(str[i]) == 1)
				i++;
		else
			i++;
		if (i < size && meta_char(str[i]) == 2)
		{
			printf("test4\n");
			return (token_message(str[i]));
		}
		i++;
	}
	return (0);
}
