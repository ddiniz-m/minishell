/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:49:39 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/13 12:51:43 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all(t_pipex *pipex, int *fd)
{
	if (fd[1] != -1)
		close(fd[1]);
	if (fd[0] != -1)
		close(fd[0]);
	if (pipex->fd_infile[0] != -1)
		close(pipex->fd_infile[0]);
	if (pipex->fd_outfile[0] != -1)
		close(pipex->fd_outfile[0]);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i++])
		free(arr[i]);
	free(arr);
}