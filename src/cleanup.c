#include "../inc/minishell.h"

/**
 * @brief Cleans up a single command's redirection file names
 *
 * @param[out] cmd Pointer to command structure
 */
static void	cleanup_redirection(t_cmd *cmd)
{
	if (cmd->redirection.input_file_name)
	{
		free(cmd->redirection.input_file_name);
		cmd->redirection.input_file_name = NULL;
	}
	if (cmd->redirection.output_file_name)
	{
		free(cmd->redirection.output_file_name);
		cmd->redirection.output_file_name = NULL;
	}
}

/**
 * @brief Cleans up and frees command linked list
 *
 * @param[out] cmd Pointer to pointer of command linked list head
 */
void	cleanup_commands(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd || !*cmd)
		return ;
	current = *cmd;
	while (current)
	{
		next = current->next;
		if (current->arguments)
			free_array(&current->arguments);
		cleanup_redirection(current);
		free(current);
		current = next;
	}
	*cmd = NULL;
}

/**
 * @brief Cleans up and frees all allocated memory in t_data structure
 *
 * @param[out] data Pointer to t_data structure to clean up
 */
void	cleanup_data(t_data *data)
{
	if (DEBUG)
		printf("=== cleanup_data() ===\n\n");

	// Clean up input
	if (data->input)
		free_and_null(&data->input);

	// Clean up tokens array
	if (data->tokens)
		free_array(&data->tokens);

	// Clean up commands
	if (data->command)
		cleanup_commands(&data->command);

	if (DEBUG)
		printf("=== cleanup complete ===\n\n");
}
