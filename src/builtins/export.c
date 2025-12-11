/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:16:57 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/11 19:02:47 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add an array of @p `args` to the end of @p `envp`.
 *
 * If the `NAME` of @p `args` matches that of an already existing
 * environmental variable, and contains `=`, it will instead replace the
 * variable. If allocation for the new environmental variable fails, the current
 * one will remain unchanged.
 *
 * @param[out]	envp	Linked list containing all environmental variables.
 * @param[in]	args	Environmental variable to add to the linked list.
 *
 * @return `0` on success, or `1` on failure.
 *
 * @warning Caller owns `free()`.
 *
 * @note @p `args` can only contain alphabetical characters, numbers and
 * @note underscores, but cannot start with numbers.
 */
int	builtin_export(t_list *envp, char **args)
{
	size_t	i;
	int		exit_code;

	i = 0;
	exit_code = EXIT_SUCCESS;
	while (args[i])
	{
		if (builtin_export_var(envp, args[i]) == EXIT_FAILURE)
		{
			exit_code = EXIT_FAILURE;
		}
		i += 1;
	}
	return (exit_code);
}

int	handle_export(t_cmd *cmd, t_data *data)
{
	int	exit_status;

	if (!cmd->args[1])
		return (export_print(data->envp));
	exit_status = 0;
	if (builtin_export(data->envp, cmd->args + 1) == EXIT_FAILURE)
	{
		exit_status = EXIT_FAILURE;
	}
	data->exit_status = exit_status;
	return (exit_status);
}
