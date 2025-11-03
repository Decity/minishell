/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:02:01 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/29 12:14:38 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void	execution(t_data *data)
{
	if (!data->command->next)
		execute_single_cmd(data->command, llist_to_array(data->envp));
	else
		execute_cmds(data);
}

void	execute_single_cmd(t_cmd *cmd, char **envp)
{
	// if (is_built_in())
	// 	execute_built_in();
	// else
		apply_redirections(cmd);
		execute_binary(cmd, envp);
}

void	execute_cmds(t_data *data)
{
	t_cmd	*current;
	pid_t	*pids;
	int		*pipefd;
	int		prev_pipefd;
	char	**envp;
	size_t	i;

	envp = llist_to_array(data->envp);
	pids = malloc(get_cmds_count(data->command) * sizeof(pid_t));
	pipefd = malloc (2 * sizeof(int));
	current = data->command;
	i = 0;
	while (current)
	{
		if (current->next != NULL)
			pipe(pipefd);

		pids[i] = fork();
		if (pids[i] == 0)
		{
			setup_child_redirections(pipefd, prev_pipefd, i == 0, current->next == NULL);
			close_pipes(pipefd, prev_pipefd, i == 0, current->next == NULL);
			execute_single_cmd(current, envp);
			exit(1);
		}

		if (i > 0)
			close(prev_pipefd);
		if (current->next != NULL)
		{
			prev_pipefd = pipefd[0];
			close(pipefd[1]);
		}

		current = current->next;
		i++;
	}
	
	// wait for pids
	while (i)
	{
		wait(NULL);
		i--;
	}
	
}

void	execute_binary(t_cmd *cmd, char **envp)
{
	char	*path;

	path = get_executable_path(cmd->args[0]);
	execve(path, cmd->args, envp);
	exit(1);
}

