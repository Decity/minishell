/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/11/17 11:52:32 by dbakker          ###   ########.fr       */
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
void	run(t_data *data)
{
	if (set_input(data) == FAILURE)	// TODO: Fix whitespace still passing through
		return ;

	set_tokens(data);
	ed_parsing(data);
	heredoc(data);
	apply_shell_expansions(data);
	set_redirections(data);
	execution(data);

	if (DEBUG)
		debug(data);

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
