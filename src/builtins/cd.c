/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:30:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/01 09:52:31 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*builtin_update_pwd_env(t_list *envp, t_pwd *dir)
{
	char	*pwd;
	char	*old_pwd;
	char	*export;

	if (ft_getenv(envp, "PWD"))
		pwd = ft_strjoin("PWD", dir->pwd);
	export = builtin_export(envp, pwd);
	if (export == NULL)
		return (free(pwd), NULL);
	if (ft_getenv(envp, "OLDPWD"))
		old_pwd = ft_strjoin("OLDPWD", dir->old_pwd);
	export = builtin_export(envp, old_pwd);
	if (export == NULL)
		return (free(old_pwd), NULL);
	free(pwd);
	free(old_pwd);
	return (envp);
}

/**
 * @brief Change directory and update the environmental variables
 * @brief `PWD` and `OLDPWD`.
 *
 * @param[out]	envp	Update `VALUE` of `PWD` and `OLDPWD`.
 * @param[out]	dir		Member variables to update.
 * @param[in]	path	Path to go to.
 *
 * @retval `0` on success.
 * @retval `1` on failure.
 * @retval `2` on malloc failure.
 */
int	builtin_cd(t_list *envp, t_pwd *dir, const char *path)
{
	if (chdir(path) == 0)
	{
		if (builtin_update_pwd(dir) == NULL)
			return (2);
		if (builtin_update_pwd_env(envp, dir) == NULL)
			return (2);
		return (0);
	}
	return (1);
}
