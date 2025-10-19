/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:30:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/18 22:50:14 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Change directory and update the environmental variables
 * @brief `PWD` and `OLDPWD`.
 *
 * @param[out]	list		Update `VALUE` of `PWD` and `OLDPWD`.
 * @param[out]	directory	Member variables to update.
 * @param[in]	path		Path to go to.
 *
 * @retval`-1` on failure.
 * @retval `0` on success.
 * @retval `1` on malloc failure.
 */
int	ed_change_directory(t_list *list, t_pwd *directory, const char *path)
{
	char	*pwd;
	char	*old_pwd;

	if (chdir(path) == 0)
	{
		if (ed_update_pwd(directory) == NULL)
			return (1);
		pwd = ft_strjoin("PWD=", directory->pwd);
		old_pwd = ft_strjoin("OLDPWD=", directory->old_pwd);
		if (pwd == NULL || old_pwd == NULL)
			return (free(pwd), free(old_pwd), 1);
		if (export_env(list, pwd) == NULL)
			return (1);
		if (export_env(list, old_pwd) == NULL)
			return (1);
		return (0);
	}
	return (-1);
}
