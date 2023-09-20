/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:08:39 by mortins-          #+#    #+#             */

/*   Updated: 2023/09/20 17:48:04 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_home(char *buf)
{
	if (!getenv("HOME")) // replace with our env
	{
		write(2, "Minishell: cd: HOME is undefined\n", 29);
		free(buf);
			// NEED TO CHANGE EXIT_STATUS
		return (-1);
	}
	else if (chdir(getenv("HOME")) != 0)  // replace with our env
	{
		perror("Minishell: cd: HOME");
		free(buf);
		// NEED TO CHANGE EXIT_STATUS
		return (-1);
	}
	// $OLDPWD = buf;
	// $PWD = getcwd();
	free(buf);
	// NEED TO CHANGE EXIT_STATUS
	return (0);
}

// Returns 0 on success.
// Returns -1 on error
int	cd(char *path)
{
	char	buf[PATH_MAX + 1];

	getcwd(buf, sizeof(buf));
	if (!path || !path[0])
		return (cd_home(buf));
	else if (chdir(path) != 0)
	{
		perror("Minishell: cd");
		free(buf);
		// NEED TO CHANGE EXIT_STATUS
		return (-1);
	}
	// $OLDPWD = buf;
	// $PWD = getcwd();
	free(buf);
	// NEED TO CHANGE EXIT_STATUS
	return (0);
}
