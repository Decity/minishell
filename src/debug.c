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
	printf("== Input: ");
	if (data->input)
		printf("'%s'\n", data->input);
	else
		printf("NULL\n");

	// Print tokens array
	printf("== Tokens: ");
	if (data->tokens)
	{
		printf("[\n");
		i = 0;
		while (data->tokens[i])
		{
			printf("=   [%d]: %s\n", i, data->tokens[i]);
			i++;
		}
		printf("=  ]\n");
		printf("== Total tokens: %d\n", i);
	}
	else
		printf("NULL\n");

	// Print command linked list
	printf("== Commands: ");
	if (data->command)
	{
		t_cmd *current = data->command;
		int cmd_index = 0;

		printf("[\n");
		while (current)
		{
			printf("=  Command [%d]:\n", cmd_index);
			printf("=   Arguments: ");
			if (current->arguments)
			{
				printf("[\n");
				i = 0;
				while (current->arguments[i])
				{
					printf("=     [%d]: '%s'\n", i, current->arguments[i]);
					i++;
				}
				printf("=    ] (Total: %d)\n", i);
			}
			else
				printf("NULL\n");

			printf("=   Redirections:\n");
			printf("=     Type: %d\n", current->redirection.redirection_type);
			printf("=     Input FD: %d\n", current->redirection.input_fd);
			printf("=     Output FD: %d\n", current->redirection.output_fd);
			printf("=     Input File: %s\n", current->redirection.input_file_name ? current->redirection.input_file_name : "NULL");
			printf("=     Output File: %s\n", current->redirection.output_file_name ? current->redirection.output_file_name : "NULL");
			printf("=   Next: %p\n", (void *)current->next);
			printf("==\n");

			current = current->next;
			cmd_index++;
		}
		printf("=  ] (Total commands: %d)\n", cmd_index);
	}
	else
		printf("NULL\n");

	printf("=== END DEBUG ===\n");
}