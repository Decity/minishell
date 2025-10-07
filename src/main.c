/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/10/07 15:09:22 by dbakker          ###   ########.fr       */
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
	char dest[100] = "Hello";
	char *src = " World";
	printf("%i%s\n", ft_strlcat(dest, src, 4), dest);
	data.envp = environ;
	while (42)
	{
		run(&data);
	}

	return (0);
}
