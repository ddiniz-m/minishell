/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:29:16 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/22 12:26:11 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Converts a (char *) to an (unsigned long long int)
unsigned long long int	exit_atoull(const char *s)
{
	unsigned long long	num;
	unsigned long long	i;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		else if (s[i] == '-' || s[i] == '+')
			i++;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			num = (num * 10) + (s[i] - '0');
			i++;
		}
	}
	return (num);
}

// Checks if arg has any formatting errors: alpha chars, multiple '-'/'+',
// special chars, '-'/'+' out of place, etc.
int	exit_format_error(char *arg)
{
	char	quotes;
	int		i;
	int		n;

	i = 0;
	quotes = 0;
	n = 0;
	while (arg && arg[i])
	{
		if (!quotes && arg[i] && (arg[i] == '\'' || arg[i] == '\"'))
			quotes = arg[i];
		else if (arg[i] && !n && (arg[i] == '-' || arg[i] == '+'))
			n = 1;
		else if (arg[i] && arg[i] != quotes && !ft_isdigit(arg[i]))
		{
			quotes = 0;
			printf("Minishell: exit: %s: numeric argument required\n", arg);
			return (1);
		}
		else if (quotes && arg[i] && arg[i] == quotes)
			quotes = 0;
		i++;
	}
	return (0);
}

/*
	In bash, <exit [n]> prints an error if n is larger than LLONG_MAX or smaller
	than LLONG_MIN. Therefore I had to create a function that could convert
	(char)n into a number larger than a long long int, so an unsigned long long
	int. By checking if n contains a '-' I know if the number is negative or not,
	so that I can add 1 to LLONG_MAX on line 94.17. (since exit_atoull() converts
	n to an unsigned number).
*/
void	ft_exit(t_minishell *ms, char *arg)
{
	int		i;
	int		fd;
	int		neg;

	i = 0;
	int EXIT_STATUS = 0;
	fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("exit\n");
	neg = 0;
	if (arg && arg[i])
	{
		if (ft_strchr(arg,'-'))
			neg = 1;
		if (exit_format_error(arg))
			EXIT_STATUS = 2; // have to change EXIT_STATUS
		else if (0 <= exit_atoull(arg) && exit_atoull(arg) <= 255)
			EXIT_STATUS = (int)exit_atoull(arg); // have to change EXIT_STATUS
		else if (exit_atoull(arg) > (unsigned long long)(LLONG_MAX + neg))
			printf("Minishell: exit: %s: numeric argument required\n", arg);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free_ms(ms);
}
