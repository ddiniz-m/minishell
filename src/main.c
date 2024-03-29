/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/07 12:44:18 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig = 0;

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
void	main_free(t_minishell *ms, int ac, char **av)
{
	post_process_signal();
	signal_exit(ms);
	free(ms->str);
	free(ms->prompt);
	free_array(ms->main_arr);
	if (ms->fdin_buf != -1)
		close(ms->fdin_buf);
	if (ms->fdout_buf != -1)
		close(ms->fdout_buf);
	(void)ac;
	(void)av;
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	if (!ms)
		malloc_error(ms);
	ms->env = env_init(envp);
	ms->exp = export_init(ms);
	ms->exit = 0;
	while (1)
	{
		signal_init();
		ms->prompt = set_prompt(ms);
		ms->str = readline(ms->prompt);
		if (ft_strlen(ms->str) != 0)
			add_history(ms->str);
		if (ms->str && syntax_error(ms))
			continue ;
		if (!var_init(ms))
		{
			run(ms);
			free_cmd_list(ms->cmdlist);
		}
		main_free(ms, ac, av);
	}
	exit(ms->exit);
}
