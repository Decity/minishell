/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:09:32 by elie              #+#    #+#             */
/*   Updated: 2025/12/08 10:32:10 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Return the expansion of the first variable of @p `arg`.
 *
 * This function assumes that @p `arg` starts right after a `$`.
 *
 * @param[in] arg	String from the command line argument.
 * @param[in] data	Data struct containing the linked list of environmental
 * 					variables and most recent `exit_status`.
 *
 * @return New pointer to the expanded variable of @p `arg`, or `NULL` on
 * @return failure.
 *
 * @warning Caller owns `free()`.
 */
char	*expand_variable(const char *arg, const t_data *data)
{
	size_t	varlen;
	char	*envval;

	if (*arg == '?')
	{
		return (ft_itoa(data->exit_status));
	}
	else
	{
		varlen = expansion_varlen(arg);
		envval = ft_getnenv(data->envp, arg, varlen);
		if (envval == NULL)
		{
			return (ft_strdup(""));
		}
		return (ft_strdup(envval));
	}
}

/**
 * @brief Create a new string with the first variable of @p `arg` expanded.
 *
 * @param[in] arg	String from the command line argument.
 * @param[in] data	Data struct containing the linked list of environmental
 * 					variables and most recent `exit_status`.
 *
 * @return Pointer to the new string with the first variable of @p `arg`
 * @return expanded, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
char	*expand_string(char *arg, size_t idx, const t_data *data)
{
	const size_t	new_strlen = expansion_new_strlen(arg, idx, data);
	char			*strret;
	char			*envval;

	envval = expand_variable(arg + idx, data);
	if (envval == NULL)
	{
		return (NULL);
	}
	strret = ft_calloc(new_strlen, sizeof(char));
	if (strret == NULL)
	{
		return (NULL);
	}
	expansion_copy(strret, arg, envval);
	free(envval);
	free(arg);
	return (strret);
}

/**
 * @brief Expand all variables of @p `arg`.
 *
 * @param[in] arg	String from the command line argument.
 * @param[in] data	Data struct containing the linked list of environmental
 * 					variables and most recent `exit_status`.
 *
 * @return New pointer with all variables expanded, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
char	*expand_variables(char *arg, t_data *data)
{
	size_t	i;
	bool	quote_single;
	bool	quote_double;

	i = 0;
	quote_single = false;
	quote_double = false;
	while (arg[i])
	{
		if (quote_single == false && arg[i] == '\"')
			quote_double = !quote_double;
		else if (quote_double == false && arg[i] == '\'')
			quote_single = !quote_single;
		if (quote_single == false && arg[i] == '$')
		{
			arg = expand_string(arg, i + 1, data);
			if (arg == NULL)
			{
				return (NULL);
			}
			continue ;
		}
		i += 1;
	}
	return (arg);
}

/**
 * @brief Expand all variables of @p `args`.
 *
 * @param[in] args	Array of strings from the command line argument.
 * @param[in] data	Data struct containing the linked list of environmental
 * 					variables and most recent `exit_status`
 *
 * @return New pointer to the array of strings, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
char	**expand_arguments(char **args, t_data *data)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		args[i] = expand_variables(args[i], data);
		args[i] = expansion_remove_quotation(args[i]);
		if (args[i] == NULL)
		{
			return (NULL);
		}
		i += 1;
	}
	return (args);
}

/**
 * @brief Apply expansion to all command line arguments.
 *
 * @param[in,out] data Data struct containing command line arguments.
 *
 * @return Pointer to @p `data`, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
t_data	*expansion(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->command;
	while (cmd)
	{
		cmd->args = expand_arguments(cmd->args, data);
		if (cmd->args == NULL)
		{
			return (NULL);
		}
		cmd = cmd->next;
	}
	return (data);
}
