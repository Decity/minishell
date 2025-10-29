/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/10/23 14:56:26 by elie             ###   ########.fr       */
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
	set_redirections(data);
	if (DEBUG)
		debug(data);
	execution(data);
	// cleanup();
}

int	main(int argc, char **argv)
{
	t_data	data;
	extern const char **environ;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(data));
	data.envp = array_to_llist(environ);
	data.directory.pwd = ft_calloc(1, sizeof(1));
	while (42)
	{
		run(&data);
	}

	return (0);
}
