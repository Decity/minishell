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

void	exit_cleanup(t_data *data)
{
	cleanup_data(data);

	// Clean up environment list
	if (data->envp)
		ft_listclear(&data->envp, free);

	// Clean up directory
	if (data->directory.pwd)
		free(data->directory.pwd);
}
