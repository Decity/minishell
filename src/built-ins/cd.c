/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:30:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/17 15:27:10 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Change directory and update the member variables of @p `directory`.
 *
 * @param[out]	directory	Member variables to update.
 * @param[in]	path		Path to go to.
 */
int	ed_change_directory(t_pwd *directory, const char *path)
{
	if (chdir(path) == 0)
	{
		ed_update_pwd(directory);
		return (0);
	}
	return (-1);
}