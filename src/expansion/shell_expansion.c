/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:09:32 by elie              #+#    #+#             */
/*   Updated: 2025/10/09 15:46:46 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// TODO: 'x''x' results into x x instead of xx

/**
 * @brief Performs the shell expansions by rewriting the argument in @p `data->command->arguments`
 *
 * - Expands the env variables
 * - Expands tilde
 * - Removes quotation marks
 */
void	apply_shell_expansions(t_data *data)
{
	char	**arguments;
	size_t	i;

	if (DEBUG)
		printf("=== apply_shell_expansions ===\n\n");

	i = 0;
	arguments = data->command->arguments;
	while (arguments[i])
	{
		expand_tilde(&arguments[i]);
		expand_env_variables(&arguments[i]);
		remove_quotation(&arguments[i]);
		i++;
	}


	if (DEBUG)
	{
		printf("== After expansions: \n");
		printf("= args: %li\n", i);
		i = 0;
		while (arguments[i])
			printf("= [%li] %s\n", i, arguments[i]), i++;
		printf("=== END SHELL_EXPANSIONS ===\n\n");
	}
}

/**
 * @brief Expands a single given argument from data->command->arguments.
 *
 * @param str A pointer to the string to perfom expansions on
 */
void	expand_env_variables(char **str)
{
	size_t	i;
	size_t	j;
	bool	inside_single_quotes;
	bool	inside_double_quotes;

	inside_single_quotes = false;
	inside_double_quotes = false;
	i = 0;
	while ((*str)[i])
	{
		if (inside_double_quotes == false && (*str)[i] == '\'')
			inside_single_quotes = !inside_single_quotes;

		if (inside_single_quotes == false && (*str)[i] == '\"')
			inside_double_quotes = !inside_double_quotes;

		if (inside_single_quotes == false && (*str)[i] == '$')
		{
			j = expand_single_variable(str, i); // +1 or na?
			// if (j = -1)
			// 	TODO: handle error
			i += j;

		}
		i++;
	}
}

/**
 * @brief Expands a single variable that starts at @p `str[index]`
 *
 * @param str the string with the paramater to be expanded
 * @param index the index of where the variable starts in the given str
 */
size_t	expand_single_variable(char **str, size_t index)
{
	char *parameter_var;
	char *parameter_name;
	char *parameter_value;
	char *new_parameter;

	if (DEBUG)
	{
		printf("== expand_single_variable() \n");
	}

	// $TERM or ${TERM}
	parameter_var = get_parameter_var(*str + index);
	if (parameter_var == NULL)
		return (-1);
	if (DEBUG)
		printf("= Parameter_var: %s\n", parameter_var);

	// TERM
	parameter_name = get_parameter_name(parameter_var);
	if (parameter_name == NULL)
		return (free_and_null(&parameter_var), -1);
	if (DEBUG)
		printf("= Parameter_name: %s\n", parameter_name);

	// xterm-kitty
	parameter_value = getenv(parameter_name); // TODO: Replace with own getenv. Can't free system's getenv.
	if (parameter_value == NULL)
		return (free_and_null(&parameter_var), free_and_null(&parameter_name), -1);
	if (DEBUG)
		printf("= Parameter_value: %s\n", parameter_value);

	// Rewrite the str with the replacements
	new_parameter = ft_strreplace(*str, parameter_var, parameter_value);
	if (new_parameter == NULL)
		return (free_and_null(&parameter_var), free_and_null(&parameter_name), free_and_null(&parameter_value), -1);

	ft_repoint(str, new_parameter);

	return (ft_strlen(parameter_value));
}

