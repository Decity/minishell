/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:54:20 by elie              #+#    #+#             */
/*   Updated: 2025/12/09 17:36:27 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

static void	set_redirection_input(t_cmd *curr_cmd, t_data *data);
static void	set_redirection_output(t_cmd *curr_cmd, t_data *data);

void	set_redirections(t_data *data)
{
	t_cmd	*curr_cmd;

	curr_cmd = data->command;
	while (curr_cmd)
	{
		set_redirection_input(curr_cmd, data);
		set_redirection_output(curr_cmd, data);
		data->exit_status = errno;
		curr_cmd = curr_cmd->next;
	}
}

static void	set_redirection_input(t_cmd *curr_cmd, t_data *data)
{
	size_t	i;

	i = 0;
	while (curr_cmd->rdr.infile && curr_cmd->rdr.infile[i].file)
	{
		if (curr_cmd->rdr.i_fd != STDIN_FILENO && curr_cmd->rdr.i_fd != -1)
			close(curr_cmd->rdr.i_fd);
		if (curr_cmd->rdr.infile[i].redir_type == TYPE_REDIRECTION_IN)
		{
			curr_cmd->rdr.i_fd = open(curr_cmd->rdr.infile[i].file, O_RDONLY);
			if (curr_cmd->rdr.i_fd == -1)
				perror(curr_cmd->rdr.infile[i].file);
		}
		else if (curr_cmd->rdr.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
		{
			curr_cmd->rdr.i_fd = open(curr_cmd->rdr.infile[i].file, O_RDONLY);
			if (curr_cmd->rdr.i_fd == -1)
				perror(curr_cmd->rdr.infile[i].file);
		}
		i++;
	}
	data->exit_status = errno;
}

static void	set_redirection_output(t_cmd *curr_cmd, t_data *data)
{
	size_t	i;

	i = 0;
	while (curr_cmd->rdr.outfile && curr_cmd->rdr.outfile[i].file)
	{
		if (curr_cmd->rdr.o_fd != STDOUT_FILENO && curr_cmd->rdr.o_fd != -1)
			close(curr_cmd->rdr.o_fd);
		if (curr_cmd->rdr.outfile[i].redir_type == TYPE_REDIRECTION_OUT)
			curr_cmd->rdr.o_fd = open(curr_cmd->rdr.outfile[i].file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (curr_cmd->rdr.outfile[i].redir_type == TYPE_REDIRECTION_APPEND)
			curr_cmd->rdr.o_fd = open(curr_cmd->rdr.outfile[i].file,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (curr_cmd->rdr.o_fd == -1)
		{
			perror(curr_cmd->rdr.outfile[i].file);
			curr_cmd->rdr.o_fd = -1;
		}
		i++;
	}
	data->exit_status = errno;
}

/**
 * @brief Close all redirection file descriptors in parent process
 *
 * After execution completes, close any open file descriptors
 * that were opened for redirections to prevent FD leaks.
 *
 * @param[in,out] data Shell data structure with commands
 */
void	close_redirection_fds(t_data *data)
{
	t_cmd	*current_cmd;

	current_cmd = data->command;
	while (current_cmd)
	{
		if (current_cmd->rdr.i_fd != STDIN_FILENO
			&& current_cmd->rdr.i_fd != -1)
		{
			close(current_cmd->rdr.i_fd);
			current_cmd->rdr.i_fd = -1;
		}
		if (current_cmd->rdr.o_fd != STDOUT_FILENO
			&& current_cmd->rdr.o_fd != -1)
		{
			close(current_cmd->rdr.o_fd);
			current_cmd->rdr.o_fd = -1;
		}
		current_cmd = current_cmd->next;
	}
}
