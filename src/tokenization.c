#include "../inc/minishell.h"

// Breaks the input into words and operators, obeying the quoting rules described in Quoting.
// These tokens are separated by metacharacters. This step performs alias expansion (see Aliases)

/**
 * @brief Sets tokens from data->input to data->tokens
 *
 * Example usage:
 * - in: data->input: 'echo "hello" ${TERM} > test.txt'
 * - out: Tokenized array: ["echo", "\"hello\"", "${TERM}", ">", "test.txt"]
 */
void	set_tokens(t_data *data)
{
	if (DEBUG)
		printf("=== set_tokens ===\n\n");

	data->tokens = malloc(sizeof(char *) * 5);
	if (!data->tokens)
		return ;

	data->tokens[0] = ft_strdup("ls");
	data->tokens[1] = ft_strdup("-la");
	data->tokens[2] = ft_strdup(">");
	data->tokens[3] = ft_strdup("test.txt");
	data->tokens[4] = NULL; // NULL terminator
}

// /**
//  * @brief Sets tokens from data->input to data->tokens
//  *
//  * Example usage:
//  * - in: data->input: 'echo "hello" ${TERM} > test.txt'
//  * - out: Tokenized array: ["echo", "\"hello\"", "${TERM}", ">", "test.txt"]
//  */
// void	set_tokens(t_data *data)
// {
// 	if (DEBUG)
// 		printf("=== set_tokens ===\n\n");

// 	data->tokens = malloc(sizeof(char *) * 6);
// 	if (!data->tokens)
// 		return ;

// 	data->tokens[0] = ft_strdup("echo");
// 	data->tokens[1] = ft_strdup("\"hello\"");
// 	data->tokens[2] = ft_strdup("${TERM}");
// 	data->tokens[3] = ft_strdup(">");
// 	data->tokens[4] = ft_strdup("test.txt");
// 	data->tokens[5] = NULL; // NULL terminator
// }