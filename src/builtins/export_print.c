/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:57:35 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/10 18:22:18 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Compare two environment variable names for sorting.
 *
 * @param[in]	a	First string to compare.
 * @param[in]	b	Second string to compare.
 *
 * @return Negative if a < b, positive if a > b, zero if equal.
 */
static int	env_strcmp(const char *a, const char *b)
{
	size_t	i;

	i = 0;
	while (a[i] && b[i] && a[i] != '=' && b[i] != '=')
	{
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	if ((a[i] == '=' || a[i] == '\0') && (b[i] == '=' || b[i] == '\0'))
		return (0);
	if (a[i] == '=' || a[i] == '\0')
		return (-1);
	return (1);
}

/**
 * @brief Create a sorted array of environment variable strings.
 *
 * @param[in]	list	Linked list of environment variables.
 *
 * @return Null-terminated array of pointers to environment strings, or NULL on failure.
 *
 * @warning Caller owns free().
 */
static char	**create_sorted_array(const t_list *list)
{
	char		**arr;
	size_t		count;
	size_t		i;
	size_t		j;
	const t_list	*tmp;

	count = 0;
	tmp = list;
	while (tmp && ++count)
		tmp = tmp->next;
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (list && i < count)
	{
		arr[i++] = (char *)list->content;
		list = list->next;
	}
	arr[i] = NULL;
	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (env_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = (t_list *)arr[i];
				arr[i] = arr[j];
				arr[j] = (char *)tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

/**
 * @brief Print out all environmental variables to stdout in sorted order.
 *
 * Variables with values are printed as: export NAME="VALUE"
 * Variables without values are printed as: export NAME
 *
 * @param[in]	list	Linked list of environment variables.
 *
 * @retval 0 on success.
 * @retval 1 on allocation failure.
 */
int	export_print(const t_list *list)
{
	char	**sorted;
	size_t	i;
	char	*value;
	size_t	namelen;

	sorted = create_sorted_array(list);
	if (!sorted)
		return (1);
	i = 0;
	while (sorted[i])
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		if (ft_strchr(sorted[i], '='))
		{
			namelen = env_namelen(sorted[i]);
			write(STDOUT_FILENO, sorted[i], namelen);
			write(STDOUT_FILENO, "=\"", 2);
			value = sorted[i] + namelen + 1;
			ft_putstr_fd(value, STDOUT_FILENO);
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
		{
			ft_putendl_fd(sorted[i], STDOUT_FILENO);
		}
		i++;
	}
	free(sorted);
	return (0);
}

/**
 * @brief Validate that a string is a valid environment variable identifier.
 *
 * @param[in]	str	String to validate (may include "NAME" or "NAME=VALUE").
 *
 * @retval true if the identifier (NAME part) is valid.
 * @retval false if the identifier is invalid.
 */
static bool	is_valid_identifier(const char *str)
{
	size_t	i;

	i = 0;
	if (*str == '\0' || ft_isdigit(*str) || *str == '=')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Handle the export builtin command with multiple arguments.
 *
 * Behavior:
 * - No args: prints all environment variables in "export NAME="VALUE"" format
 * - With args: exports each variable, validates identifiers
 * - Invalid identifiers print an error but don't stop processing
 *
 * @param[in]		cmd		Command structure containing arguments.
 * @param[in,out]	data	Shell data containing environment and exit status.
 *
 * @retval 0 if all operations succeeded.
 * @retval 1 if any identifier was invalid or export failed.
 */
int	handle_export(t_cmd *cmd, t_data *data)
{
	int		i;
	int		exit_status;

	if (!cmd->args[1])
		return (export_print(data->envp));
	exit_status = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			exit_status = 1;
		}
		else if (builtin_export(data->envp, cmd->args[i]) == NULL)
			exit_status = 1;
		i++;
	}
	data->exit_status = exit_status;
	return (exit_status);
}
