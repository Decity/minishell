/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:05:55 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/14 15:16:20 by dbakker          ###   ########.fr       */
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
	t_cmd	*cmd;
	size_t	node_i = 0;
	size_t	i;

	printf("\n=== Parsing Start ===\n\n");
	printf("String to parse\n\e[96m%s\e[0m\n\n", data->input);
	// while (cmd)
	// {

	// 	printf(" \e[93m-->\e[0m ");
	// 	cmd = cmd->next;
	// }
	// printf("%p\n\n", cmd);
	cmd = data->command;
	while (cmd)
	{
		printf("------------\n");
		printf("\e[93mNode %zu -\e[0m ", node_i);
		printf("[");
		for (i = 0; cmd->args[i]; i++)
		{
			printf("\"%s\", ", cmd->args[i]);
		}
		printf("%s]\n", cmd->args[i]);
		for (i = 0; cmd->redirect.infile[i].file; i++)
		{
			printf("Input file: %s | ", cmd->redirect.infile[i].file);
			printf("Input redirection type: %i\n", cmd->redirect.infile[i].redir_type);
		}
		printf("Input file descriptor: %i\n", cmd->redirect.input_fd);
		for (i = 0; cmd->redirect.outfile[i].file; i++)
		{
			printf("Output file: %s | ", cmd->redirect.outfile[i].file);
			printf("Output redirection type: %i\n", cmd->redirect.outfile[i].redir_type);
		}
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
