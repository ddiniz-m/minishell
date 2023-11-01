/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:54:54 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/01 16:44:06 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reset_fds(t_minishell *ms)
{
	dup2(ms->fdout_buf, STDOUT_FILENO);
	close(ms->fdout_buf);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
}

void	redirect_in(char *file, int heredoc)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		open_error(file);
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		if (heredoc)
			unlink(file);
	}
}

void	redirect_out(char *file, int append)
{
	int	fd;

	if (!append)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	else
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (fd < 0)
		open_error(file);
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	redirect(char **main_arr, int pos)
{
	int		index;

	index = pos;
	while (main_arr[index] && main_arr[index][0] && ft_strcmp(main_arr[\
		index], "|") != 0)
	{
		if (ft_strcmp(main_arr[index], "<") == 0)
			redirect_in(main_arr[index + 1], 0);
		else if (ft_strcmp(main_arr[index], "<<") == 0)
			redirect_in(main_arr[index + 1], 1);
		else if (ft_strcmp(main_arr[index], ">") == 0)
			redirect_out(main_arr[index + 1], 0);
		else if (ft_strcmp(main_arr[index], ">>") == 0)
			redirect_out(main_arr[index + 1], 1);
		index++;
	}
}