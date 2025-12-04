/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/12/02 14:55:28 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

/**
 * @brief Execute one iteration of the shell main loop
 *
 * Reads input, tokenizes, parses, expands variables, sets up redirections,
 * executes the command, and cleans up.
 *
 * @param[in,out] data Shell data structure
 */
static void	run(t_data *data)
{
	if (set_input(data) == FAILURE)
		return ;
	if (set_tokens(data) == FAILURE)
		return ;
	parsing(data);
	heredoc(data);
	apply_shell_expansions(data);
	set_redirections(data);

	if (DEBUG)
		debug(data);

	execution(data);
	remove_heredoc_files(data->command);
	cleanup_data(data);
}

/**
 * @brief Execute a single command in non-interactive mode (-c flag)
 *
 * @param[in,out] data Shell data structure
 * @param[in] command Command string to execute
 */
static void	run_command(t_data *data, const char *command)
{
	data->input = ft_strdup(command);
	if (!data->input)
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		data->exit_status = 1;
		exit(data->exit_status);
	}
	if (set_tokens(data) == FAILURE)
	{
		cleanup_data(data);
		return ;
	}
	parsing(data);
	heredoc(data);
	apply_shell_expansions(data);
	set_redirections(data);
	if (DEBUG)
		debug(data);
	execution(data);
	remove_heredoc_files(data->command);
	cleanup_data(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init(&data);
	if (argc >= 3 && ft_strcmp(argv[1], "-c") == 0)
	{
		data.is_interactive = false;
		run_command(&data, argv[2]);
		exit_cleanup(&data);
		return (data.exit_status);
	}
	while (42)
	{
		run(&data);
	}
	return (0);
}
