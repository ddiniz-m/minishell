/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:03:12 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/27 15:47:49 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_file_in(t_content *content, t_list *lst)
{
	content->fd_in = open(lst->data, O_RDONLY);
	if (content->fd_in < 0)
		return (printf("OPEN ERROR\n"));
	dup2(content->fd_in, STDIN_FILENO);
	close(content->fd_in);
	return (0);
}

int	open_file_hdoc(t_content *content, t_list *lst)
{
	content->fd_in = open(lst->data, O_RDONLY);
	if (content->fd_in < 0)
		return (printf("OPEN ERROR\n"));
	dup2(content->fd_in, STDIN_FILENO);
	close(content->fd_in);
	return (0);
}

int	open_file_out(t_content *content, t_list *lst)
{
	content->fd_out = open(lst->data, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (content->fd_out < 0)
		return (printf("OPEN ERROR\n"));
	dup2(content->fd_out, STDOUT_FILENO);
	close(content->fd_out);
	return (0);
}

int	open_file_app(t_content *content, t_list *lst)
{
	content->fd_out = open(lst->data, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (content->fd_out < 0)
		return (printf("OPEN ERROR\n"));
	dup2(content->fd_out, STDOUT_FILENO);
	close(content->fd_out);
	return (0);
}