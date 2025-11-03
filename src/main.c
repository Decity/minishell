/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/10/29 12:13:22 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run(t_data *data)
{
	// Get input
	data->input = readline("> ");

	set_tokens(data);
	ed_parsing(data);
	// apply_shell_expansions(data);
	// set_redirections(data);
	if (DEBUG)
		debug(data);
	// execute(data);
	cleanup_data(data);
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
