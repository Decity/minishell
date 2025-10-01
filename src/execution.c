#include "../inc/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void	execute(t_data *data)
{
	pid_t	pid;
	int		fd;

	if (DEBUG)
		printf("=== execute_command() ===\n");

	pid = fork();
	if (pid == 0)
	{
		// Child process
		fd = open(data->command->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		execvp(data->command->arguments[0], data->command->arguments);
	}
	else
	{
		// Parent process
		wait(NULL);
	}

	// clean up data->input, data->tokens, and data->command
	cleanup_data(data);
}

