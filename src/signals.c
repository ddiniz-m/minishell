/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:08:59 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/06 11:57:44 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	CTRL-C sends an "Interrupt" signal.
//	For documentation on rl_functions, read:
//	https://tiswww.case.edu/php/chet/readline/readline.html#Command-Line-Editing
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

//	CTRL-C sends an "Interrupt" signal.
//	CTRL-\ sends a "Quit" signal.
//	When using SIG_IGN in signal(), it ignores the signal received.
void	signal_init(t_minishell *ms)
{
	(void)ms;
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

//	CTRL-D represents "No input".
//	When pressed, str is NULL and it exits the shell.
void	signal_exit(t_minishell *ms)
{
	if (!(ms->str))
	{
		printf("exit\n");
		free_ms(ms);
	}
}
