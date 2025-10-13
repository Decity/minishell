/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:52 by elie              #+#    #+#             */
/*   Updated: 2025/10/12 14:23:01 by dbakker          ###   ########.fr       */
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
	t_cmds	*example_command;

	if (DEBUG)
		printf("=== set_commands() ===\n\n");

	//doubly_linked_list(data->tokens);
	example_command = malloc(sizeof(t_cmds));
	if (example_command == NULL)
		exit(2); // TODO: What to actually do when malloc fails here?
	ft_bzero(example_command, sizeof(t_cmds));

	example_command->content = malloc(sizeof(t_parse));
	ft_bzero(example_command->content, sizeof(t_parse));

	example_command->content->arguments = copy_array(data->tokens);
	data->command = example_command;

	if (DEBUG)
		printf("=== +++ ===\n\n");
}
