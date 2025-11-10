/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:09:14 by elie              #+#    #+#             */
/*   Updated: 2025/11/10 15:06:22 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize shell data structure
 *
 * Sets up environment variables, current directory, checks if running
 * interactively, and configures signal handlers.
 *
 * @param[out] data Shell data structure to initialize
 */
void	init(t_data *data)
{
	extern const char **environ;

	ft_bzero(data, sizeof(t_data));
	data->envp = array_to_llist(environ);
	data->directory.pwd = getcwd(NULL, 0);
	data->is_interactive = isatty(STDIN_FILENO);
	if (data->is_interactive)
		setup_signals_interactive();
}

/**
 * @brief Read input from user or stdin
 *
 * Uses readline for interactive mode, get_next_line for pipes/files.
 * Exits on EOF, returns FAILURE for empty input, adds to history if valid.
 *
 * @param[in,out] data Shell data structure
 *
 * @return SUCCESS if valid input received, FAILURE if empty input
 */
uint8_t	set_input(t_data *data)
{
	size_t	len;

	if (data->is_interactive)
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
	if (!data->input)
		exit(0);
	if (!data->input[0] || ft_strlen(data->input) == 0)
	{
		free(data->input);
		return (FAILURE);
	}
	if (data->is_interactive)
		add_history(data->input);
	return (SUCCESS);
}
