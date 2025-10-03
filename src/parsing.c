#include "../inc/minishell.h"

// Parses the tokens into simple and compound commands (see Shell Commands).

/**
 * @brief Parse commands
 *
 * Example usage:
 * - Data->tokens: ["echo", "\"hello\", ${TERM}", ">", "test.txt"]
 *
 * - command->arguments: ["echo", "\"hello\", ${TERM}"]
 * - command->redirection: ">"
 * - command->inpput: stdin
 * - command->output: "test.txt"
 */
void	set_commands(t_data *data)
{
	if (DEBUG)
		printf("=== set_commands() ===\n\n");

	t_commands *example_command;

	example_command = malloc(sizeof(t_commands));

	example_command->arguments = malloc(sizeof(char *) * 3);
	if (example_command->arguments == NULL)
		return ;

	example_command->arguments[0] = ft_strdup("ls");
	example_command->arguments[1] = ft_strdup("-la");
	example_command->arguments[2] = NULL;
	example_command->redirection = ft_strdup(">");
	example_command->input = NULL;
	example_command->output = ft_strdup("test.txt");

	data->command = example_command;
}

// /**
//  * @brief Parse commands
//  *
//  * Example usage:
//  * - Data->tokens: ["echo", "\"hello\", ${TERM}", ">", "test.txt"]
//  *
//  * - command->arguments: ["echo", "\"hello\", ${TERM}"]
//  * - command->redirection: ">"
//  * - command->inpput: stdin
//  * - command->output: "test.txt"
//  */
// void	set_commands(t_data *data)
// {
// 	if (DEBUG)
// 		printf("=== set_commands() ===\n\n");

// 	t_commands *example_command;

// 	example_command = malloc(sizeof(t_commands));

// 	example_command->arguments = malloc(sizeof(char *) * 4);

// 	example_command->arguments[0] = ft_strdup("echo");
// 	example_command->arguments[1] = ft_strdup("\"hello\"");
// 	example_command->arguments[2] = ft_strdup("${TERM}");
// 	example_command->arguments[3] = NULL;
// 	example_command->redirection = ft_strdup(">");
// 	example_command->input = NULL;
// 	example_command->output = ft_strdup("test.txt");

// 	data->command = example_command;
// }