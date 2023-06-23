/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/20 18:57:28 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(void)
{
	char	*str;
	t_var	*var;

	var = var_struct_init();
	signal_init();
	while (1)
	{
		var->prompt = set_prompt();
		str = readline(var->prompt);
		var_init(var, str);
		parse_main(var);
		add_history(str);
		signal_exit(var, str);
		free(str);
		free(var->prompt);
		arr_free(var->main_arr);
	}
	free(var);
}
