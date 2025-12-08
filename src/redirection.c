/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:54:20 by elie              #+#    #+#             */
/*   Updated: 2025/12/08 14:53:04 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/*
 TODO:
	Open needs error check
*/

void	set_redirections(t_data *data)
{
	t_cmd	*current_cmd;
	size_t	i;

	current_cmd = data->command;
	while (current_cmd)
	{
		// INPUT
		i = 0;
		while (current_cmd->redirect.infile && current_cmd->redirect.infile[i].file)
		{
			// Close previous input fd if it's not stdin
			if (current_cmd->redirect.input_fd != STDIN_FILENO && current_cmd->redirect.input_fd != -1)
				close(current_cmd->redirect.input_fd);

			if (current_cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_IN)
			{
				current_cmd->redirect.input_fd = open(current_cmd->redirect.infile[i].file, O_RDONLY);
				if (current_cmd->redirect.input_fd == -1)
				{
					perror(current_cmd->redirect.infile[i].file);
					current_cmd->redirect.input_fd = -1;
				}
			}
			else if (current_cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				current_cmd->redirect.input_fd = open(current_cmd->redirect.infile[i].file, O_RDONLY);
				if (current_cmd->redirect.input_fd == -1)
				{
					perror(current_cmd->redirect.infile[i].file);
					current_cmd->redirect.input_fd = -1;
				}
			}
			i++;
		}

		// OUTPUT
		i = 0;
		while (current_cmd->redirect.outfile && current_cmd->redirect.outfile[i].file)
		{
			// Close previous output fd if it's not stdout
			if (current_cmd->redirect.output_fd != STDOUT_FILENO && current_cmd->redirect.output_fd != -1)
				close(current_cmd->redirect.output_fd);

			if (current_cmd->redirect.outfile[i].redir_type == TYPE_REDIRECTION_OUT)
				current_cmd->redirect.output_fd = open(current_cmd->redirect.outfile[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

			else if (current_cmd->redirect.outfile[i].redir_type == TYPE_REDIRECTION_APPEND)
				current_cmd->redirect.output_fd = open(current_cmd->redirect.outfile[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);

			if (current_cmd->redirect.output_fd == -1)
			{
				perror(current_cmd->redirect.outfile[i].file);
				current_cmd->redirect.output_fd = -1;
			}
			i++;
		}

		current_cmd = current_cmd->next;
	}
}
