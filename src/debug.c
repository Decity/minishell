/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:05:55 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/29 11:38:50 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void debug_tokens(t_data *data)
{
	int	i;

	// Print input string
	printf("\n== Input: ");
	if (data->input)
		printf("'%s'\n", data->input);
	else
		printf("NULL\n");

	// Print tokens array
	printf("== Tokens: ");
	if (data->tokens)
	{
		printf("[\n");
		i = 0;
		while (data->tokens[i])
		{
			printf("=   [%d]: %s\n", i, data->tokens[i]);
			i++;
		}
		printf("=  ]\n");
		printf("== Total tokens: %d\n", i);
	}
	else
		printf("NULL\n");
}

static void debug_parsing(t_data *data)
{
	t_cmd	*cmd = data->command;
	size_t	node_i = 0;
	size_t	i;

	printf("\n=== Parsing Start ===\n\n");
	while (cmd)
	{
		printf("[");
		for (i = 0; cmd->args[i]; i++)
		{
			printf("\"%s\", ", cmd->args[i]);
		}
		printf("%s]", cmd->args[i]);
		printf(" \e[93m-->\e[0m ");
		cmd = cmd->next;
	}
	printf("%p\n\n", cmd);
	cmd = data->command;
	while (cmd)
	{
		printf("\e[93mNode %zu -\e[0m ", node_i);
		printf("Input file: %s | ", cmd->redirect.infile->file);
		printf("Input redirection type: %i | ", cmd->redirect.infile->redir_type);
		printf("Input file descriptor: %i | ", cmd->redirect.input_fd);
		printf("Output file: %s | ", cmd->redirect.outfile->file);
		printf("Output redirection type: %i | ", cmd->redirect.outfile->redir_type);
		printf("Output file descriptor: %i\n", cmd->redirect.output_fd);
		cmd = cmd->next;
		node_i++;
	}
	printf("\n=== Parsing End ===\n");
}

void	debug(t_data *data)
{
	if (!data)
	{
		printf("DEBUG: data is NULL\n");
		return ;
	}
	printf("=== DEBUG OUTPUT ===\n");
	debug_tokens(data);
	debug_parsing(data);
	printf("\n=== END DEBUG ===\n");
}
