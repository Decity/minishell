#include "minishell.h"

/**
 * @brief Cleans up and frees all allocated memory in t_data structure
 *
 * @param[out] data Pointer to t_data structure to clean up
 */
void	cleanup_data(t_data *data)
{
	if (DEBUG)
		printf("\n=== cleanup_data() ===\n");

	// Clean up input
	if (data->input)
		free_and_null(&data->input);

	// Clean up tokens array
	if (data->tokens)
		free_array(&data->tokens);

	// Clean up commands
	if (data->command)
		ed_cmdclear(&data->command);

	if (DEBUG)
		printf("\n=== cleanup complete ===\n");
}
