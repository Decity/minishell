/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:47 by elie              #+#    #+#             */
/*   Updated: 2025/11/05 15:21:35 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	run(t_data *data)
{
	set_input(data);
	set_tokens(data);
	ed_parsing(data);
	apply_shell_expansions(data);
	set_redirections(data);
	setup_signals_executing();
	execution(data);
	setup_signals_interactive();

	if (DEBUG)
		debug(data);
		
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
