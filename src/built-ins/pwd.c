/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:05:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/04 18:04:17 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Prints current working directory
void	pwd(void)
{
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
		while (cwd[i])
			cwd[i++] = 0;
	}
	else
	{
		perror("Error");
		exit_status = errno;
		return ;
	}
	exit_status = 0;
}
// PATH_MAX is defined in <limits.h> and represents the maximum length of a
// file path on the current system (including the null terminator).
