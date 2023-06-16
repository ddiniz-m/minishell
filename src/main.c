/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/16 17:24:01 by ddiniz-m         ###   ########.fr       */
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

//readline records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main()
{
	char		*str;
	t_var		*var;

	var = malloc(sizeof(t_var));
	while (1)
	{
		str = readline("\033[0;33mMinishell >$ \033[0m");
		var_init(var, str);
		parse_main(var, str);
		add_history(str);
		signal_init(str);
		free(str);
	}
}
