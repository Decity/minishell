/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:15:33 by ebelle            #+#    #+#             */
/*   Updated: 2025/12/08 17:16:14 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Cleans up and frees all allocated memory in t_data structure
 *
 * @param[out] data Pointer to t_data structure to clean up
 */
void	cleanup_data(t_data *data)
{
	if (data->input)
	{
		free_and_null(&data->input);
	}
	if (data->tokens)
	{
		free_array(&data->tokens);
	}
	if (data->command)
	{
		cmdclear(&data->command);
	}
}

/**
 * @brief Clean up all resources and exit the program
 *
 * Calls cleanup_data, frees environment list and directory, then exits.
 *
 * @param[in,out] data Shell data structure to clean up
 * @param[in] exit_code Exit code to pass to exit()
 */
void	exit_cleanup(t_data *data, int exit_code)
{
	cleanup_data(data);
	if (data->envp)
	{
		ft_listclear(&data->envp, free);
	}
	if (data->directory.pwd)
	{
		free(data->directory.pwd);
	}
	if (data->directory.old_pwd)
	{
		free(data->directory.old_pwd);
	}
	exit(exit_code);
}

void	full_cleanup(t_data *data)
{
	cleanup_data(data);
	if (data->envp)
	{
		ft_listclear(&data->envp, free);
	}
	if (data->directory.pwd)
	{
		free(data->directory.pwd);
	}
	if (data->directory.old_pwd)
	{
		free(data->directory.old_pwd);
	}
}
