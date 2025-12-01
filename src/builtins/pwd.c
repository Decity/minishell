/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:41:14 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/29 21:00:02 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Update the path of the current working directory.
 *
 * @param[out] directory Store the `VALUE` of `PWD` and `OLDPWD`.
 *
 * @return Pointer to @p `directory`, or NULL on failure.
 *
 * @warning Caller owns `free()`.
 */
void	*builtin_update_pwd(t_pwd *directory)
{
	char	*ptr_old_pwd;
	char	*ptr_pwd;

	ptr_old_pwd = ft_strdup(directory->pwd);
	if (ptr_old_pwd == NULL)
	{
		return (NULL);
	}
	free(directory->old_pwd);
	directory->old_pwd = ptr_old_pwd;
	ptr_pwd = getcwd(NULL, 0);
	if (ptr_pwd == NULL)
	{
		return (NULL);
	}
	free(directory->pwd);
	directory->pwd = ptr_pwd;
	return (directory);
}

/**
 * @brief Print the current directory to `stdout`.
 */
void	pwd_print(t_pwd directory)
{
	printf("%s\n", directory.pwd);
}