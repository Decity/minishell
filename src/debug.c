#include "../inc/minishell.h"

void	debug(t_data *data)
{
	int	i;

	if (!data)
	{
		printf("DEBUG: data is NULL\n");
		return ;
	}

	printf("=== DEBUG OUTPUT ===\n");

	// Print input string
	printf("Input: ");
	if (data->input)
		printf("'%s'\n", data->input);
	else
		printf("NULL\n");

	// Print tokens array
	printf("Tokens: ");
	if (data->tokens)
	{
		printf("[\n");
		i = 0;
		while (data->tokens[i])
		{
			printf("  [%d]: '%s'\n", i, data->tokens[i]);
			i++;
		}
		printf("]\n");
		printf("Total tokens: %d\n", i);
	}
	else
		printf("NULL\n");

	printf("=== END DEBUG ===\n");
}