/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:29:42 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/10 10:21:07 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if a string represents a valid numeric argument for exit.
 *
 * A valid number may optionally start with '+' or '-', followed by one or
 * more digits. Empty strings or strings with only a sign are invalid.
 *
 * @param[in]	str	String to validate.
 *
 * @retval true if the string is a valid number.
 * @retval false if the string is not a valid number.
 */
static bool	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Check if a numeric string would overflow when parsed.
 *
 * Detects if the number would exceed LLONG_MAX during conversion.
 *
 * @param[in]	str	Numeric string to check (must be valid number format).
 *
 * @retval true if the number would overflow.
 * @retval false if the number fits in a long long.
 */
static bool	is_overflow(const char *str)
{
	long long	result;
	int			i;

	i = 0;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			return (true);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (false);
}

/**
 * @brief Parse a numeric string into an exit code (0-255).
 *
 * Converts the string to a number and applies modulo 256 to get a valid
 * exit code. Handles both positive and negative numbers. The result is
 * always in the range 0-255 to match bash behavior.
 *
 * @param[in]	str	Numeric string to parse (must be valid number format).
 *
 * @return Exit code in the range 0-255.
 */
static int	parse_exit_code(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)((result * sign) % 256));
}

/**
 * @brief Exit the shell with an optional exit code.
 *
 * Implements the exit builtin command. Behavior:
 * - No args: exits with last exit status
 * - One numeric arg: exits with that code (mod 256)
 * - Non-numeric arg: prints error and exits with code 2
 * - Multiple args: prints error, sets exit status to 1, but doesn't exit
 *
 * Prints "exit" to stderr before exiting (bash behavior).
 *
 * @param[in]		cmd		Command structure containing arguments.
 * @param[in,out]	data	Shell data containing exit status.
 *
 * @note This function may not return if exit conditions are met.
 */
void	builtin_exit(t_cmd *cmd, t_data *data)
{
	char	**args;
	int		exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	args = cmd->args;
	if (!args[1])
		exit_cleanup(data, data->exit_status);
	if (!is_valid_number(args[1]) || is_overflow(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit_cleanup(data, 2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		data->exit_status = 1;
		return ;
	}
	exit_code = parse_exit_code(args[1]);
	exit_cleanup(data, exit_code);
}
