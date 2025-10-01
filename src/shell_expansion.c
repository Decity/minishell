#include "../inc/minishell.h"

// Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames
// (see Filename Expansion) and commands and arguments.

void	set_shell_expansions(t_data *data)
{
	if (DEBUG)
		printf("=== set_shell_expansions ===\n\n");

	// "hello" -> hello
	free(data->command->arguments[1]);
	data->command->arguments[1] = ft_strdup("hello");

	// ${TERM} -> xterm-kitty
	free(data->command->arguments[2]);
	data->command->arguments[2] = ft_strdup("xterm-kitty");

}