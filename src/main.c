/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/10/15 17:51:28 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	run(t_data *data)
{
	// Get input
	data->input = readline("> ");

	set_tokens(data);
	set_commands(data);
	apply_shell_expansions(data);
	// set_redirections(data);
	if (DEBUG)
		debug(data);
	execute(data);
	// cleanup();
}

int	main(int argc, char **argv)
{
	t_data	data;
	extern char **environ;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(data));
	data.envp = array_to_llist((const char **)environ);
	while (42)
	{
		run(&data);
	}

	return (0);
}
