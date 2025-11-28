/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:09:32 by elie              #+#    #+#             */
/*   Updated: 2025/11/28 12:12:22 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Performs the shell expansions by rewriting the argument in @p `data->command->arguments`
 *
 * - Expands the env variables
 * - Removes quotation marks
 */
void	apply_shell_expansions(t_data *data)
{
	char	**arguments;
	size_t	i;

	if (DEBUG)
		printf("=== apply_shell_expansions ===\n\n");

	i = 0;
	arguments = data->command->args;
	while (arguments[i])
	{
		if (expand_env_variables(&arguments[i], data) == FAILURE)
		{
			exit_cleanup(data);
			exit(data->exit_status);
		}
		if (remove_quotation(&arguments[i]) == FAILURE)
		{
			exit_cleanup(data);
			exit(data->exit_status);
		}
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
 * @param envp Environment variables list
 */
int8_t	expand_env_variables(char **str, t_data *data)
{
	int		i;
	int		j;
	bool	inside_single_quotes;
	bool	inside_double_quotes;

	inside_single_quotes = false;
	inside_double_quotes = false;
	j = 0;
	i = 0;
	while ((*str)[i])
	{
		if (inside_double_quotes == false && (*str)[i] == '\'')
			inside_single_quotes = !inside_single_quotes;

		if (inside_single_quotes == false && (*str)[i] == '\"')
			inside_double_quotes = !inside_double_quotes;

		if (inside_single_quotes == false && (*str)[i] == '$')
		{
			j = expand_single_variable(str, i, data);
			if (j == -1)
				return (FAILURE);
			i += j;

		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Expands the $? special parameter (exit status)
 *
 * @param str the string with the $? to be expanded
 * @param parameter_var the "$?" string to replace
 * @param data shell data containing exit_status
 * @return length of replacement string, or -1 on failure
 */
static int	expand_last_exit_status(char **str, t_data *data)
{
	char	*exit_status_str;
	char	*new_parameter;
	int		len;

	exit_status_str = ft_itoa(data->exit_status);
	if (!exit_status_str)
		return (FAILURE);
	len = ft_strlen(exit_status_str);
	new_parameter = ft_strreplace(*str, "$?", exit_status_str);
	free(exit_status_str);
	if (new_parameter == NULL)
		return (FAILURE);
	ft_repoint(str, new_parameter);
	return (len);
}

/**
 * @brief Expands a single variable that starts at @p `str[index]`
 *
 * @param str the string with the paramater to be expanded
 * @param index the index of where the variable starts in the given str
 * @param envp Environment variables list
 */
int	expand_single_variable(char **str, size_t index, t_data *data)
{
	char *parameter_var;
	char *parameter_name;
	char *parameter_value;
	char *new_parameter;

	if (DEBUG)
		printf("== expand_single_variable() \n");
	parameter_var = get_parameter_var(*str + index);
	if (parameter_var == NULL)
		return (-1);
	if (DEBUG)
		printf("= Parameter_var: %s\n", parameter_var);
	if (ft_strcmp(parameter_var, "$?") == 0)
		return (expand_last_exit_status(str, data));
	parameter_name = get_parameter_name(parameter_var);
	if (parameter_name == NULL)
		return (free_and_null(&parameter_var), -1);
	if (DEBUG)
		printf("= Parameter_name: %s\n", parameter_name);
	parameter_value = ft_getenv(data->envp, parameter_name);
	if (parameter_value == NULL)
		parameter_value = "";
	if (DEBUG)
		printf("= Parameter_value: %s\n", parameter_value);
	new_parameter = ft_strreplace(*str, parameter_var, parameter_value);
	free_and_null(&parameter_var);
	free_and_null(&parameter_name);
	if (new_parameter == NULL)
		return (-1);
	ft_repoint(str, new_parameter);
	return (ft_strlen(parameter_value));
}

