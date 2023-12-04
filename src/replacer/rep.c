/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:37:02 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/04 19:48:18 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
char	**var_split(char *str);

// So, the ideia is to only replace the env variables, not dealing with quotes.
// To do so, we need to check first if the var is inside single quotes, beacuse
//	when it's inside double quotes, it gets repalced all the same.
// I'm thinking in making a function that checks whether there is a $ inside quotes;


/*
	Old replacer functions used so far:
	var_iter();
	var_cmp();
*/

// If $? return 2
// If $3 replace with NULL
// While str[i] is alphanumerical or '_' i++
int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (meta_char(str[i]) != 4)
		return (0);
	i++;
	if (str[i] && (str[i] == '?' || ft_isdigit(str[i])))
		return (2);
	while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

/* void	rep(t_minishell *ms)
{
	int		i;
	int		size;
	int		str_size;
	int		j;
	int		var_size;
	int		buf_size;

	char	*pre;
	char	*var;
	char	*buf;
	char	*buf1;
	char	*replaced_var;

	i = 0;
	buf = NULL;
	buf1 = NULL;
	j = 0;
	buf_size = 0;
	var_size = 0;
	size = arr_size(ms->main_arr);
	while (i < size)
	{
		j = 0;
		str_size = ft_strlen(ms->main_arr[i] + 1);
		if (ft_strchr(ms->main_arr[i], '$') == 0)
		{
			i++;
			continue;
		}
		while (j < str_size)
		{
			j = strlen_chr(ms->main_arr[i], '$');
			pre = ft_strndup(ms->main_arr[i], j);
			printf("pre: %s\n", pre);

			var_size = var_len(ms->main_arr[i] + j + 1) + 1;
			var = ft_strndup(ms->main_arr[i] + j, var_size);
			printf("var: %s\n", var);

			replaced_var = var_iter(ms->env, var + 1);
			free(var);
			buf = ft_strjoin(pre, replaced_var);
			free(pre);
			free(replaced_var);

			buf1 = ft_strjoin(buf1, buf);
			free(buf);
			j += var_size;
		}
		i++;
	}
} */

// This function replaces one environment variable with its value
char	*rep2(t_minishell *ms, char *result, char quotes, int str_index)
{
	char	*var;
	char	*fix; //as in suffix and prefix
	char	*buffer;

	var = NULL;
	fix = NULL;
	buffer = NULL;
	fix = ft_strndup(result, str_index); // get prefix
	if (!(meta_char(result[str_index + 1]) == 3 && !quotes))
		buffer = ft_strndup(result + str_index, get_var_len(result + str_index)); // get environment value (E.g: $HOME)
	if (buffer && ft_strcmp(buffer, "$") == 0)	//
		var = ft_strdup(buffer);				// This gets the environment variable value
	else if (buffer)							// (E.g: /nfs/homes/mortins-)
		var = var_iter(ms->env, buffer + 1);	//
	free(buffer);
	buffer = ft_strjoin(fix, var); // Join prefix and the replaced var
	free(fix);
	fix = ft_strdup(result + str_index + get_var_len(result + str_index)); // get suffix
	free(var);
	free(result);
	result = ft_strjoin(buffer, fix); // Join prefix+var and suffix
	free(buffer);
	free(fix);
	return(result);
}

size_t	get_new_index(t_minishell *ms, char *result, char quotes, int str_index)
{
	int		new_index;
	char	*var;
	char	*buffer;

	var = NULL;
	buffer = NULL;
	new_index = 0;
	if (!(meta_char(result[str_index + 1]) == 3 && !quotes))
		buffer = ft_strndup(result + str_index, get_var_len(result + str_index));
	if (buffer && ft_strcmp(buffer, "$") == 0)
		var = ft_strdup(buffer);
	else if (buffer)
		var = var_iter(ms->env, buffer + 1);
	new_index = ft_strlen(var);
	free(buffer);
	free(var);
	return(new_index);
}

// This function goes through every string in the main_arr and replaces
// environment variables with their value
// It does not yet move the strings in the array when one is replaced with NULL
void	rep(t_minishell *ms)
{
	char	*result;
	int		str_index;
	int		arr_index;
	size_t	var_len;
	char	quotes;

	result = NULL;
	arr_index = 0;
	var_len = 0;
	while (ms->main_arr[arr_index])
	{
		quotes = '\0';
		if (!ft_strchr(ms->main_arr[arr_index], '$'))
		{
			arr_index++;
			continue ;
		}
		str_index = 0;
		result = ft_strdup(ms->main_arr[arr_index]);
		while (result && result[str_index])
		{
			if (!quotes && meta_char(result[str_index]) == 3)			// If not inside quotes and encounters a quote mark
				quotes = result[str_index];								//		Flag as inside the quote mark (' or ")
			else if (quotes && result[str_index] == quotes)				// If inside quotes and finds the closing quote mark
				quotes = '\0';											//		Flag as no longer inside quotes
			if (result[str_index] == '$' && quotes != '\'')				// If looking at a $ and not inside single quote marks
			{
				var_len = get_new_index(ms, result, quotes, str_index);	//		Get length of the value
				result = rep2(ms, result, quotes, str_index);			//		Get value
				str_index += var_len - 1;								//		Add length of value to the index
			}
			str_index++;
		}
		printf("RESULT: %s\n\n", result);
		// free(main_arr[arr_index]);
		// main_arr[arr_index] = ft_strdup(result);
		free(result);
		arr_index++;
	}
}

// Cases to be prepared
// $"HOME" = HOME
// "$"HOME = $HOME
// $3HOME = HOME
