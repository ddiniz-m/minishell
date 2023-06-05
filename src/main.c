/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/05 17:42:14 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_path_from_env(void)
{
	char *str;

	str = getenv("PATH");
	printf("\nPATH = %s\n", str);
}

void	get_files_dirs(void)
{
	DIR				*folder;
	struct dirent	*buf;

	printf("\nFiles and Directories:\n");
	folder = opendir(".");
	while ((buf = readdir(folder)))
		printf("%s\n", buf->d_name);
	closedir(folder);
}

void	get_directory(void)
{
	printf("Current Directory = %s\n", getcwd(NULL, 0));
}

void	ctrl_c(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main()
{
	char	*str;

	get_directory();
	get_files_dirs();
	get_path_from_env();

	printf("\nMinishell\n");
	while (1)
	{
		signal(SIGINT, ctrl_c);
		str = readline("$ ");
		add_history(str);
		free(str);		
	}
}