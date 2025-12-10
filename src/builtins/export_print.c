/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:57:35 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/10 23:45:58 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print out all environmental variables to `stdout`.
 *
 * Should be used if `export` gets called without arguments. At which variables
 * get printed as `declare -x NAME="VALUE"`.
 */
int	export_print(const t_list *list)
{
	const char	declare_x[] = "declare -x ";
	char		*str_env;

	while (list)
	{
		write(STDOUT_FILENO, declare_x, sizeof(declare_x) - 1);
		write(STDOUT_FILENO, list->content, env_namelen((char *)list->content));
		str_env = ft_getenv(list, (char *)list->content);
		if (str_env == NULL)
		{
			printf("\n");
		}
		else
		{
			printf("=\"%s\"\n", ft_getenv(list, (char *)list->content));
		}
		list = list->next;
	}
	return (0);
}

int	handle_export(t_cmd *cmd, t_data *data)
{
	if (cmd->args[1])
	{
		data->exit_status = builtin_export(data->envp, cmd->args + 1);
		return (data->exit_status);
	}
	else
	{
		return (export_print(data->envp));
	}
}
