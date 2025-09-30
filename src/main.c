#include "../inc/minishell.h"

void	run(t_data *data)
{
	// Get input
	data->input = readline(">");

	// // Tokenize
	// set_tokens(data);

	// // Parse tokens to commands
	// set_commands(data);

	// // Shell expansions
	// set_shell_expansions(data)

	// // Redirections
	// set_redirections(data);

	// // Execute
	// execute(data);
	debug(data);
}


int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	while (42)
	{
		run(&data);
	}

	// exit_cleanup();
	return (0);
}
