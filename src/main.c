/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/27 19:29:14 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	g_exit = 0;
struct sigaction	signal_change(struct sigaction *old);
void				signal_init(struct sigaction *new, struct sigaction *old);

int	main(int ac, char **av, char **envp)
{
	t_minishell			*ms;
	struct sigaction	new;

	ms = malloc(sizeof(t_minishell));
	ms->env = env_init(envp);
	ms->exp = export_init(ms->env);
	signal_init(NULL, &ms->og_sigint);
	while (1)
	{
		ms->prompt = set_prompt(ms);
		ms->str = readline(ms->prompt);
		add_history(ms->str);
		if (ms->str && syntax_error(ms))
			continue ;
		var_init(ms);
		new = signal_change(&ms->og_sigint);
		run(ms);
		signal_init(&ms->og_sigint, &new);
		signal_exit(ms);
		free(ms->str);
		free(ms->prompt);
		free_array(ms->main_arr);
		free_cmd_list(ms->cmdlist);
	}
	(void)av;
	(void)ac;
	exit (g_exit);
}

// `>output>>append echo 1 2 3 <input<<heredoc | <in<<here ls -l >out>>app`
