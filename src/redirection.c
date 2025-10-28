/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:54:20 by elie              #+#    #+#             */
/*   Updated: 2025/10/26 15:35:05 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/*
 TODO:
	Open needs error check
	Deal with heredoc
*/

void	set_redirections(t_data *data)
{
	if (DEBUG)
		printf("=== set_redirections ===\n\n");

	t_cmd	*current_cmd;

	current_cmd = data->command;
	while (current_cmd)
	{
		if (current_cmd->redirection.outfile->redir_type == TYPE_REDIRECTION_OUT)
			current_cmd->redirection.output_fd = open(current_cmd->redirection.outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (current_cmd->redirection.infile->redir_type == TYPE_REDIRECTION_IN)
			current_cmd->redirection.input_fd = open(current_cmd->redirection.outfile->file, O_RDONLY);
		if (current_cmd->redirection.outfile->redir_type == TYPE_REDIRECTION_APPEND)
			current_cmd->redirection.output_fd = open(current_cmd->redirection.outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);


		// if (current_cmd->redirection.redirection_type == TYPE_REDIRECTION_OUT)
		// 	current_cmd->redirection.output_fd = open(current_cmd->redirection.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// if (current_cmd->redirection.redirection_type == TYPE_REDIRECTION_IN)
		// 	current_cmd->redirection.input_fd = open(current_cmd->redirection.infile, O_RDONLY);
		// if (current_cmd->redirection.redirection_type == TYPE_REDIRECTION_APPEND)
		// 	current_cmd->redirection.output_fd = open(current_cmd->redirection.outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);

		current_cmd = current_cmd->next;
	}
}