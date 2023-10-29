/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:08:59 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/27 19:29:54 by ddiniz-m         ###   ########.fr       */
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
		g_exit = 128 + SIGINT;
	}
}

//	CTRL-C sends an "Interrupt" signal.
//	CTRL-\ sends a "Quit" signal.
//	When using SIG_IGN in signal(), it ignores the signal received.
/* void	signal_init(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}
 */
//	CTRL-D represents "No input".
//	When pressed, str is NULL and it exits the shell.
void	signal_exit(t_minishell *ms)
{
	if (!(ms->str))
	{
		/* write(2, "exit\n", 5); */
		free_ms(ms);
	}
}

void	signal_process_interrupt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signal_init(struct sigaction *new, struct sigaction *old)
{
	sigaction(SIGINT, new, old);
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

struct sigaction	signal_change(struct sigaction *old)
{
	struct sigaction new;
	
	sigemptyset(&new.sa_mask);
	new.sa_handler = signal_process_interrupt;
	new.sa_flags = 0;
	sigaction(SIGINT, &new, old);
	signal(SIGQUIT, SIG_IGN);
	return (new);
}