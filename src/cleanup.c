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
		if (data->command->content->arguments)
			free_array(&data->command->content->arguments);

		if (data->command->content->redirection)
			free(data->command->content->redirection);

		if (data->command->content->input)
			free(data->command->content->input);

		if (data->command->content->output)
			free(data->command->content->output);

		free(data->command);
		data->command = NULL;
	}

	if (DEBUG)
		printf("=== cleanup complete ===\n\n");
}
