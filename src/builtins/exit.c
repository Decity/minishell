/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:29:42 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/28 12:24:19 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_exit(t_data *data)
{
	ft_putstr_fd("exit", STDERR_FILENO);
	exit_cleanup(data);
	exit(data->exit_status);
}