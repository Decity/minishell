/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/12/11 19:34:34 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (parsing(data) == FAILURE)
		exit_cleanup(data, EXIT_FAILURE);
	if (heredoc(data) == FAILURE)
		exit_cleanup(data, EXIT_FAILURE);
	if (expansion(data) == FAILURE)
		exit_cleanup(data, EXIT_FAILURE);
	set_redirections(data);
	execution(data);
	close_redirection_fds(data);
	remove_heredoc_files(data->command);
	cleanup_data(data);
}

int	main(void)
{
	t_data	data;

	init(&data);
	while (42)
	{
		run(&data);
	}
	return (0);
}
