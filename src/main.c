/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/16 13:42:39 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//CTRL-C sends a "Interrupt" signal.
//Don't want to explain rl functions, go read:
//https://tiswww.case.edu/php/chet/readline/readline.html#Command-Line-Editing
void	signal_interrupt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}	
}

//CTRL-D represents "No input", so when it is pressed, "str" is NULL and it
//	exits.
//CTRL-\ sends a "Quit" signal. When using SIG_IGN in signal(), it ignores 
//	the signal recieved.
void	signal_init(char *str)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
	if (!str)
	{
		printf("exit\n");
		free(str);
		exit (0);
	}
}

//	readline records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("Minishell >$ ");
		add_history(str);
		signal_init(str);
		free(str);
	}
}
