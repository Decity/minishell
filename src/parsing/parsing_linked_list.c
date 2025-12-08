/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_linked_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:33:35 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/08 14:45:46 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes @p `num` strings from @p `args` to the new struct.
 *
 * It will also initialize all member variables of `t_rdr` and `t_hd` to `0`,
 * with the exception of `output_fd` which gets initialized to `1`.
 *
 * @param[in] args	Array of strings.
 * @param[in] num	Amount of strings to copy to the new struct.
 *
 * @return Pointer to the struct, or `NULL` of failure.
 *
 * @warning Caller owns `free()`.
 */
t_cmd	*cmdnew(const char **args, size_t num)
{
	t_cmd	*cmd;

	if (args == NULL)
	{
		return (NULL);
	}
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		return (NULL);
	}
	cmd->args = copy_narray((char **)args, num);
	if (cmd->args == NULL)
	{
		return (free(cmd), NULL);
	}
	ft_memset(&cmd->redirect, 0, sizeof(t_rdr));
	cmd->redirect.output_fd = STDOUT_FILENO;
	cmd->next = NULL;
	return (cmd);
}

/**
 * @brief Append @p `new` to @p `head`.
 *
 * @param[out]	head	Head node of the list to append to.
 * @param[in]	new		Node to append.
 */
void	cmdadd_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*node;

	node = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (node->next)
	{
		node = node->next;
	}
	node->next = new;
}

/**
 * @brief Frees all allocated memory in @p `cmd`.
 */
void	cmddelone(t_cmd *cmd)
{
	size_t	i;

	if (cmd == NULL)
		return ;
	free_array(&cmd->args);
	i = 0;
	if (cmd->redirect.infile)
	{
		while (cmd->redirect.infile[i].file)
		{
			free(cmd->redirect.infile[i].delimiter);
			free(cmd->redirect.infile[i].file);
			i += 1;
		}
	}
	i = 0;
	if (cmd->redirect.outfile)
		while (cmd->redirect.outfile[i].file)
			free(cmd->redirect.outfile[i++].file);
	i = 0;
	free(cmd->redirect.infile);
	free(cmd->redirect.outfile);
	free(cmd);
}

/**
 * @brief Free the entire linked list of @p `cmd`.
 */
void	cmdclear(t_cmd **cmd)
{
	t_cmd	*node;
	t_cmd	*temp;

	if (cmd == NULL || *cmd == NULL)
	{
		return ;
	}
	node = *cmd;
	while (node)
	{
		temp = node->next;
		cmddelone(node);
		node = temp;
	}
	*cmd = NULL;
}

/**
 * @brief Free the entire t_redir struct.
 */
void	redirclear(t_redir *redir)
{
	size_t	i;

	i = 0;
	if (redir == NULL)
	{
		return ;
	}
	while (redir[i].file || redir[i].delimiter)
	{
		free(redir[i].file);
		free(redir[i].file);
		i += 1;
	}
	free(redir);
}
