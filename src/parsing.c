/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:52 by elie              #+#    #+#             */
/*   Updated: 2025/10/03 19:04:34 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Parses the tokens into simple and compound commands (see Shell Commands).

/**
 * @brief Parse commands
 *
 * Example usage:
 * - Data->tokens: ["echo", "\"hello\", ${TERM}", ">", "test.txt"]
 *
 *
 * - command->arguments: ["echo", "\"hello\", ${TERM}"]
 * - command->redirection: ">"
 * - command->inpput: stdin
 * - command->output: "test.txt"
 */
void	set_commands(t_data *data)
{
	t_commands	*example_command;

	if (DEBUG)
		printf("=== set_commands() ===\n\n");

	example_command = malloc(sizeof(t_commands));
	if (example_command == NULL)
		exit(2); // TODO: What to actually do when malloc fails here?

	ft_bzero(example_command, sizeof(t_commands));
	example_command->arguments = copy_array(data->tokens); // TODO: Consider storing tokens len, and using copy_narray instead()
	data->command = example_command;

	if (DEBUG)
		printf("=== +++ ===\n\n");
}
