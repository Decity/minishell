/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:30:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/11 09:51:06 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*builtin_update_pwd_env(t_list *envp, t_pwd *dir)
{
	char	*pwd;
	char	*old_pwd;
	char	*export;
	char	*old_pwd_value;
	bool	pwd_was_set;

	pwd_was_set = (ft_getenv(envp, "PWD") != NULL);
	pwd = ft_strjoin("PWD=", dir->pwd);
	if (!pwd)
		return (NULL);
	export = builtin_export(envp, pwd);
	free(pwd);
	if (export == NULL)
		return (NULL);
	if (pwd_was_set)
		old_pwd_value = dir->old_pwd;
	else
		old_pwd_value = "";
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_value);
	if (!old_pwd)
		return (NULL);
	export = builtin_export(envp, old_pwd);
	free(old_pwd);
	if (export == NULL)
		return (NULL);
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
