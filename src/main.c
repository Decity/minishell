#include "../inc/minishell.h"

void	run(t_data *data)
{
	// Get input
	data->input = readline("> ");

	set_tokens(data);
	set_commands(data);
	set_shell_expansions(data);
	set_redirections(data);
	execute(data);
	debug(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	while (42)
	{
		run(&data);
	}

	return (0);
}
