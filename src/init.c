/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:15:33 by ebelle            #+#    #+#             */
/*   Updated: 2025/12/09 12:12:09 by elie             ###   ########.fr       */
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
	extern const char	**environ;

	ft_bzero(data, sizeof(t_data));
	data->envp = array_to_llist(environ);
	data->directory.pwd = getcwd(NULL, 0);
	data->is_interactive = isatty(STDIN_FILENO);
	if (data->envp == NULL || data->directory.pwd == NULL)
	{
		perror("minishell");
		exit_cleanup(data, EXIT_FAILURE);
	}
	if (data->is_interactive)
		setup_signals_interactive();
}

static void	set_prompt(t_data *data)
{
	if (data->exit_status)
		printf("(╯°□°)╯︵ ┻━┻\n");
	data->input = readline("( ͡° ͜ʖ ͡°) ");
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
		set_prompt(data);
	else
	{
		data->input = get_next_line(STDIN_FILENO);
		if (!data->input)
			exit(data->exit_status);
		len = ft_strlen(data->input);
		if (len > 0 && data->input[len - 1] == '\n')
			data->input[len - 1] = '\0';
	}
	if (!data->input)
		exit_cleanup(data, data->exit_status);
	if (!data->input[0] || ft_strlen(data->input) == 0)
		return (free(data->input), FAILURE);
	len = 0;
	while (data->input[len] && ft_isspace(data->input[len]))
		len++;
	if (data->input[len] == '\0')
		return (free(data->input), FAILURE);
	if (data->is_interactive)
		add_history(data->input);
	return (SUCCESS);
}
