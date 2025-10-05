/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:02:01 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/03 13:39:49 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief Find @p `name` in the environment @p `envp`.
 *
 * The function will only check each line of @p `envp` equal to the length
 * of @p `name`. So truncating the NAME may return unexpected results.
 *
 * @param[in]	name	The NAME to find.
 * @param[in]	envp	The environment.
 *
 * @return Pointer to the first occurrence of NAME found in @p `envp`,
 * @return or NULL on failure.
 */
char	*get_env_name(const char *name, const char **envp)
{
	size_t	i;
	size_t	name_len;

	i = 0;
	if (name == NULL)
	{
		return (NULL);
	}
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], name, name_len))
		{
			return (envp[i]);
		}
		i++;
	}
	return (NULL);
}


char	*get_path(char *path)
{
	char	**paths;


	paths = ft_split(path, ':');
	// How do we error handle if NULL? Should we exit()?
	for (size_t i = 0; paths[i]; i++)
	{
		printf("%s\n", paths[i]);
	}
	return (NULL);
}

void	execute(t_data *data)
{
	pid_t	pid;
	int		fd;

	if (DEBUG)
		printf("=== execute_command() ===\n\n");

	char *test = get_env_name("PATH", data->envp);
	if (test == NULL)
	{
		return ;
	}
	get_path(test);
	pid = fork();
	if (pid == 0)
	{
		// Child process
		fd = open(data->command->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		execve("/usr/bin/ls", &data->command->arguments[0], data->command->arguments);
		// execvp(data->command->arguments[0], data->command->arguments);
	}
	else
	{
		// Parent process
		wait(NULL);
	}

	// clean up data->input, data->tokens, and data->command
	cleanup_data(data);
}

