/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:29:42 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/10 09:18:21 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	minishell_exit(t_cmd *cmd, t_data *data)
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
