/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/11/15 14:55:34 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	run(t_data *data)
{
	set_input(data);
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
