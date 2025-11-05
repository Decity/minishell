/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:09:14 by elie              #+#    #+#             */
/*   Updated: 2025/11/05 14:09:16 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <unistd.h>

void	init(t_data *data)
{
	extern const char **environ;

	ft_bzero(data, sizeof(t_data));
	data->envp = array_to_llist(environ);
	data->directory.pwd = ft_calloc(1, sizeof(1));
	setup_signals_interactive();
}

void	set_input(t_data *data)
{
	size_t	len;

	if (isatty(STDIN_FILENO))
		data->input = readline("> ");
	else
	{
		data->input = get_next_line(STDIN_FILENO);
		if (!data->input)
			exit(0);
		len = ft_strlen(data->input);
		if (len > 0 && data->input[len - 1] == '\n')
			data->input[len - 1] = '\0';
	}
	if (!data->input || !data->input[0])
	{
		if (data->input)
			free(data->input);
		exit(0);
	}
}
