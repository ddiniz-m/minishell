/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/22 15:03:41 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(int ac, char **av, char **env)
{
	char	*str;
	t_var	*var;

	(void)ac;
	(void)av;
	var = var_struct_init();
	signal_init();
	while (1)
	{
		str = readline("Minishell >$ ");
		var_init(var, str);
		parse_main(var, env);
		add_history(str);
		signal_exit(var, str);
		free(str);
		arr_free(var->main_arr);
	}
	free(var);
}
