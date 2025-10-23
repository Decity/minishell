/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:32:52 by elie              #+#    #+#             */
/*   Updated: 2025/10/23 15:46:15 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Parses the tokens into simple and compound commands (see Shell Commands).

/**
 * @brief Parse commands
 *
 * input:
 * - Data->tokens: ["echo", "\"hello\", ${TERM}", ">", "test.txt"]
 *
 * output:
 * - command->arguments: ["echo", "\"hello\", ${TERM}"]
 * - command->redirection->type: ">"
 * - command->redirection->input_fd: stdin
 * - command->redirection->output_fd: stdin
 * - command->redirection->outfile: "test.txt"
 * - command->redirection->infile: NULL
 */
void	set_commands(t_data *data)
{
	t_cmd	*current_command;
	size_t	i;
	size_t	j;
	char	**tokens;

	if (DEBUG)
		printf("=== set_commands() ===\n\n");

	// init command
	current_command = init_command();
	// malloc check
	data->command = current_command;

	i = 0;
	tokens = data->tokens;
	while (tokens[i])
	{
		// add arguments to the command
		j = 0;
		while (tokens[i + j] && is_redirection(tokens[i + j]) == false && tokens[i + j][0] != '|')
		{
			j++;
		}
		if (j > 0)
		{
			current_command->arguments = copy_narray(&tokens[i], j);
			i += j;
		}

		if (!tokens[i])
			break ;

		if (is_redirection(tokens[i]))
		{
			assign_redirection(&tokens[i], current_command);
			i++;
		}
		else if (tokens[i][0] == '|')
		{
			current_command->next = init_command();
			// malloc check
			current_command = current_command->next;
		}
		i++;
	}

	if (DEBUG)
		printf("=== +++ ===\n\n");
}

/**
 * @brief Checks if a string starts with a redirection operator
 * @param str String to check
 * @return true if string starts with '<' or '>', false otherwise
 */
bool	is_redirection(char *str)
{
	if (ft_strncmp("<", str, 1) == 0 || ft_strncmp(">", str, 1) == 0)
		return (true);
	return (false);
}

/**
 * @brief Initializes a new command structure
 * @return Pointer to newly allocated t_cmd structure with default values
 */
t_cmd	*init_command()
{
	t_cmd	*new_command;

	new_command = malloc(sizeof(t_cmd));
	// error check

	ft_bzero(new_command, sizeof(new_command));
	new_command->redirection.input_fd = STDIN_FILENO;
	new_command->redirection.output_fd = STDOUT_FILENO;
	return (new_command);
}

/**
 * @brief Assigns redirection to command structure
 * @param tokens Array where [0] is operator and [1] is filename
 * @param cmd Command structure to update
 */
void	assign_redirection(char **tokens, t_cmd *cmd)
{
	cmd->redirection.redirection_type = get_redirection_type(tokens[0]);

	if (cmd->redirection.redirection_type == TYPE_REDIRECTION_OUT)
		cmd->redirection.outfile = ft_strdup(tokens[1]);

	if (cmd->redirection.redirection_type == TYPE_REDIRECTION_APPEND)
		cmd->redirection.outfile = ft_strdup(tokens[1]);

	if (cmd->redirection.redirection_type == TYPE_REDIRECTION_IN)
		cmd->redirection.infile = ft_strdup(tokens[1]);
}