/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:08:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/06/23 14:58:33 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Returns 0 on success.
// Returns -1 on error
int	cd(char *path)
{
	if (!path)
	{
		if (!getenv("HOME"))
		{
			printf("Error: cd: HOME is undefined");
			// NEED TO CHANGE EXIT_STATUS
			return (-1);
		}
		else if (chdir(getenv("HOME")) != 0)
		{
			perror("Error");
			// NEED TO CHANGE EXIT_STATUS
			return (-1);
		}
		// NEED TO CHECK ACCESS TO PATH
	}
	else if (chdir(path) != 0)
	{
		perror("Error");
		// NEED TO CHANGE EXIT_STATUS
		return (-1);
	}
	// NEED TO CHANGE EXIT_STATUS
	return (0);

}
