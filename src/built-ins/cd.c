/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:30:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/17 17:55:43 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Change directory and update the member variables of @p `directory`.
 *
 * @param[out]	list		Update `VALUE` of `PWD` and `OLDPWD`.
 * @param[out]	directory	Member variables to update.
 * @param[in]	path		Path to go to.
 *
 * @return `0` on success, or `-1` on failure.
 */
int	ed_change_directory(t_list *list, t_pwd *directory, const char *path)
{
	char	*pwd;
	char	*old_pwd;

	if (chdir(path) == 0)
	{
		// Disregard the lack of NULL checks
		ed_update_pwd(directory);
		pwd = ft_strjoin("PWD=", directory->pwd);
		old_pwd = ft_strjoin("OLDPWD=", directory->old_pwd);
		export_env(list, pwd);
		export_env(list, old_pwd);
		return (0);
	}
	return (-1);
}