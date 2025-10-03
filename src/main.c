/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/10/03 19:07:27 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	run(t_data *data)
{
	// Get input
	data->input = readline("> ");

	set_tokens(data);
	set_commands(data);
	// set_shell_expansions(data);
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

	ft_bzero(&data, sizeof(data));
	data.envp = environ;
	while (42)
	{
		run(&data);
	}

	return (0);
}
