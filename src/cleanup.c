#include "../inc/minishell.h"

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

	if (data->command)
	{
		if (data->command->arguments)
			free_array(&data->command->arguments);

		if (data->command->redirection)
			free(data->command->redirection);

		if (data->command->input)
			free(data->command->input);

		if (data->command->output)
			free(data->command->output);

		free(data->command);
		data->command = NULL;
	}

	if (DEBUG)
		printf("=== cleanup complete ===\n\n");
}
