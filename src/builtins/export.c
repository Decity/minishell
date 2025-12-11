/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:16:57 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/10 18:23:13 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if @p `str_env` matches the `NAME` in `content` of @p
 * @brief `curr_node` and replace its `VALUE` if str_env contains '='.
 *
 * If str_env doesn't contain '=', the existing value is kept 
 *
 * @param[out]	curr_node	`content` to replace.
 * @param[in]	str_env		The new environmental variable.
 * @param[out]	should_free	Set to true if str_env should be freed by caller.
 *
 * @retval true if names match (variable found).
 * @retval false if names don't match.
 */
static bool	builtin_replace_env(t_list *curr_node, const char *str_env,
		bool *should_free)
{
	size_t	len_envvar;
	size_t	len_cnt;

	len_envvar = env_namelen(str_env);
	len_cnt = env_namelen(curr_node->content);
	if (ft_memcmp(curr_node->content, str_env, len_cnt) == 0
		&& len_envvar == len_cnt)
	{
		if (ft_strchr(str_env, '='))
		{
			free(curr_node->content);
			curr_node->content = (void *)str_env;
			*should_free = false;
		}
		else
		{
			*should_free = true;
		}
		return (true);
	}
	return (false);
}

/**
 * @brief Iterate through the linked list and either replace an existing
 * @brief variable, or add @p `str_env` to the end of @p `list`.
 *
 * If the variable already exists and str_env has no '=', the existing value
 * is kept and str_env is freed. If the variable doesn't exist and str_env
 * has no '=', it's added without a value (bash behavior for marking variables
 * for export).
 *
 * @param[out]	list	Linked list containing environmental variables.
 * @param[in]	str_env	String containing a NAME or NAME=VALUE.
 *
 * @return Pointer to the node added/modified, or `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
static t_list	*builtin_iterate_list(t_list *list, const char *str_env)
{
	t_list	*curr_node;
	bool	should_free;

	curr_node = list;
	while (curr_node)
	{
		should_free = false;
		if (builtin_replace_env(curr_node, str_env, &should_free))
		{
			if (should_free)
				free((void *)str_env);
			return (curr_node);
		}
		curr_node = curr_node->next;
	}
	curr_node = ft_listnew((char *)str_env);
	if (curr_node == NULL)
		return (NULL);
	ft_listadd_back(&list, curr_node);
	return (ft_listlast(list));
}

/**
 * @brief Add @p `envvar` to the end of @p `list`.
 *
 * If the `NAME` of @p `envvar` matches that of an already existing
 * environmental variable, and contains `=`, it will replace the variable.
 * If allocation for the new environmental variable fails, the current
 * one will remain unchanged.
 *
 * If @p `envvar` does not contain `=`, it will be added to the list as
 * a variable marked for export without a value (bash behavior).
 *
 * @param[out]	list	Linked list containing all environmental variables.
 * @param[in]	envvar	Environmental variable to add to the linked list.
 *
 * @retval Pointer to the node added to the list.
 * @retval Pointer to @p `list`.
 * @retval `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 *
 * @note @p `envvar` can only contain alphabetical characters, numbers and
 * @note underscores, but cannot start with numbers.
 */
void	*builtin_export(t_list *list, const char *envvar)
{
	char	*str_env;

	if (envvar == NULL)
		return (NULL);
	str_env = ft_strdup(envvar);
	if (str_env == NULL)
		return (NULL);
	list = builtin_iterate_list(list, str_env);
	return (list);
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
