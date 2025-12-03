/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:09:32 by elie              #+#    #+#             */
/*   Updated: 2025/12/03 15:37:02 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Calculate the length of @p `arg` until it encounters a non-NAME
 * @brief character.
 *
 * This function assumes that @p `arg` starts right after a `$`.
 *
 * @param[in] arg	String from the command line argument.
 *
 * @return The length of @p `arg`.
 */
size_t	expansion_varlen(const char *arg)
{
	size_t	len;

	len = 0;
	if (arg[len] == '?')
	{
		return (1);
	}
	while (ft_isalnum(arg[len]) || arg[len] == '_')
	{
		len += 1;
	}
	return (len);
}

/**
 * @brief Calculate the length of @p `arg` after expanding the first variable.
 *
 * @param[in] arg	String from the command line argument.
 * @param[in] idx	Index of the first variable.
 * @param[in] data	Data struct containing the linked list of environmental
 * 					variables and most recent `exit_status`.
 */
size_t	expansion_new_strlen(const char *arg, size_t idx, const t_data *data)
{
	const size_t	arglen = ft_strlen(arg);
	const size_t	varlen = expansion_varlen(arg + idx);
	const char		*envval = ft_getnenv(data->envp, arg + idx, varlen);
	size_t			expandlen;

	if (arg[idx] == '?')
	{
		expandlen = ft_intlen(data->exit_status);
	}
	else if (envval == NULL)
	{
		expandlen = 0;
	}
	else
	{
		expandlen = ft_strlen(envval);
	}
	return (arglen - varlen + expandlen);
}

/**
 * @brief Expand @p `arg` by duplicating the value.
 *
 * This function assumes that @p `arg` starts right after a `$`.
 *
 * @param[in] arg	String from the command line argument.
 * @param[in] data	Data struct containing the most recent `exit_status`.
 *
 * @return Pointer to the expanded value of @p `arg`, or `NULL` on failure.
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

char	*expansion_copy_before_variable(char *dest, const char *src)
{
	const char	*envvar = ft_strchr(src, '$');
	size_t		num;

	if (envvar == NULL)
	{
		num = ft_strlen(src);
	}
	else
	{
		num = envvar - src;
	}
	ft_memcpy(dest, src, num);
	if (envvar == NULL)
	{
		src = src + num;
	}
	else
	{
		src = envvar;
	}
	return ((char *)src);
}

char	*expansion_copy_variable(char *dest, const char *src)
{
	const size_t	destlen = ft_strlen(dest);
	const size_t	srclen = ft_strlen(src);

	ft_memcpy(dest + destlen, src, srclen);
	return (dest);
}

char	*expansion_copy_after_variable(char *dest, const char *src)
{
	const size_t	destlen = ft_strlen(dest);
	char			*envvar;
	size_t			envvarlen;

	envvar = ft_strchr(src, '$') + 1;
	envvar += expansion_varlen(envvar);
	envvarlen = ft_strlen(envvar);
	ft_memcpy(dest + destlen, envvar, envvarlen);
	return (dest);
}

char	*expansion_copy(char *dest, const char *src, const char *envval)
{
	expansion_copy_before_variable(dest, src);
	expansion_copy_variable(dest, envval);
	expansion_copy_after_variable(dest, src);
	return (dest);
}

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
	free(arg);
	return (strret);
}

char	*expansion_string(char *arg, t_data *data)
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
		{
			quote_double = !quote_double;
		}
		else if (quote_double == false && arg[i] == '\'')
		{
			quote_single = !quote_single;
		}
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

char	**expansion_quotes(char **args, t_data *data)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		args[i] = expansion_string(args[i], data);
		if (args[i] == NULL)
		{
			return (NULL);
		}
		i += 1;
	}
	return (args);
}

void	*expansion(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->command;
	while (cmd)
	{
		if (expansion_quotes(cmd->args, data) == NULL)
		{
			return (NULL);
		}
		cmd = cmd->next;
	}
	return (data);
}

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

