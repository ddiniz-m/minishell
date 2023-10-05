/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:08:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/05 15:38:29 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_home(void) // receive our env
{
	if (!getenv("HOME")) // replace with our env
	{
		write(2, "Minishell: cd: HOME is undefined\n", 29);
		g_exit = 1;
	}
	else if (chdir(getenv("HOME")) != 0)  // replace with our env
	{
		perror("Minishell: cd: HOME");
		g_exit = 1;
	}
	g_exit = 0;
}

void	cd(char *path)
{
	if (!path || !path[0])
		cd_home(); // send our env
	else if (chdir(path) != 0)
	{
		perror("Minishell: cd");
		g_exit = 1;
	}
	else
		g_exit = 0;
}
