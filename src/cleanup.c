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
	if (data->input)
	{
		free_and_null(&data->input);
	}
	if (data->tokens)
	{
		free_array(&data->tokens);
	}
	if (data->command)
	{
		ed_cmdclear(&data->command);
	}
	if (DEBUG)
		printf("\n=== cleanup complete ===\n");
}

/**
 * @brief Clean up all resources before program exit
 *
 * Calls cleanup_data and additionally frees environment list and directory.
 *
 * @param[in,out] data Shell data structure to clean up
 */
void	exit_cleanup(t_data *data)
{
	cleanup_data(data);
	if (data->envp)
	{
		ft_listclear(&data->envp, free);
	}
	if (data->directory.pwd)
	{
		free(data->directory.pwd);
	}
	if (data->directory.old_pwd)
	{
		free(data->directory.old_pwd);
	}
}
