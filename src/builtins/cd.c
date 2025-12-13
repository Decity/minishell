/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:30:29 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/11 18:49:00 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_update_oldpwd_env(t_list *envp, t_pwd *dir)
{
	char	*old_pwd;
	int		export;

	if (ft_getenv(envp, "PWD"))
	{
		old_pwd = ft_strjoin("OLDPWD=", dir->old_pwd);
		export = builtin_export_var(envp, old_pwd);
		free(old_pwd);
		if (export == EXIT_FAILURE)
		{
			return (FAILURE);
		}
	}
	else
	{
		old_pwd = ft_strjoin("OLDPWD=", "");
		export = builtin_export_var(envp, old_pwd);
		free(old_pwd);
		if (export == EXIT_FAILURE)
		{
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	builtin_update_pwd_env(t_list *envp, t_pwd *dir)
{
	char	*pwd;
	int		export;

	export = builtin_update_oldpwd_env(envp, dir);
	if (export == FAILURE)
	{
		return (FAILURE);
	}
	pwd = ft_strjoin("PWD=", dir->pwd);
	export = builtin_export_var(envp, pwd);
	free(pwd);
	if (export == EXIT_FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Change directory and update the environmental variables
 * @brief `PWD` and `OLDPWD`.
 *
 * @param[out]	envp	Update `VALUE` of `PWD` and `OLDPWD`.
 * @param[out]	dir		Member variables to update.
 * @param[in]	path	Path to go to.
 *
 * @return `0` on success, or `1` on failure.
 */
int	builtin_cd(t_list *envp, t_pwd *dir, const char *path)
{
	if (chdir(path) == 0)
	{
		if (builtin_update_pwd(dir) == FAILURE)
			perror("minishell");
		if (builtin_update_pwd_env(envp, dir) == FAILURE)
			perror("minishell");
		return (EXIT_SUCCESS);
	}
	perror("minishell: cd");
	return (EXIT_FAILURE);
}
