/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:08:59 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/29 23:07:47 by mira             ###   ########.fr       */
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
		printf("BBBB");
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
} */

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
		printf("AAAA");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signal_init(struct sigaction *new, __sighandler_t __handler)
{
	sigemptyset(&new->sa_mask);
	new->sa_handler = __handler;
	new->sa_flags = 0;
	sigaction(SIGINT, new, NULL);
	signal(SIGQUIT, SIG_IGN);
}
