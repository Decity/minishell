/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:34:03 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/27 22:31:42 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Count how many variables are in @p `line` and store each one in an
 * @brief array, after expanding them.
 *
 * Anything after a `$` is considered a variable. If the variable is invalid,
 * it will be replaced with an empty string instead.
 *
 * @param[in] envp Linked list containing environmental variables.
 * @param[in] line Returned string from `readline()`.
 *
 * @return Pointer to the array of variables found in @p `line`, or `NULL` on
 * @return failure.
 *
 * @warning Caller owns `free()`.
 */
static char	**heredoc_extract_variables(const t_list *envp, const char *line)
{
	const size_t	count = char_count(line, '$');
	char	**strarr;
	char	*envvar;
	size_t	i;

	strarr = ft_calloc(count + 1, sizeof(char *));
	if (strarr == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		envvar = heredoc_duplicate(line);
		if (envvar == NULL)
			return (NULL);
		strarr[i] = heredoc_expand(envp, envvar);
		if (strarr[i] == NULL)
			return (free_array(&strarr), NULL);
		free(envvar);
		line = ft_strchr(line, '$') + 1;
		i += 1;
	}
	return (strarr);
}

/**
 * @brief Calculate the length that the new string should be after all variables
 * @brief have been expanded.
 *
 * @param[in] strarr	Array of strings containing environmental variables.
 * @param[in] line		String read from `readline()`.
 *
 * @return The minimum length the new string should be.
 */
static size_t	heredoc_new_strlen(const char **strarr, const char *line)
{
	const size_t	strslen = strarrlen(strarr);
	const size_t	linelen = ft_strlen(line);
	size_t			reduce;
	size_t			i;
	size_t			varlen;

	reduce = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			varlen = heredoc_variable_length(line + i + 1);
			reduce += varlen + 1;
			i += varlen + 1;
		}
		else
		{
			i += 1;
		}
	}
	return (linelen - reduce + strslen);
}

/**
 * @brief
 */
static char	*heredoc_rewrite(const char *line, const char **strarr)
{
	const size_t	strretlen = heredoc_new_strlen((const char **)strarr, line);
	char			*strret;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	strret = ft_calloc(strretlen + 1, sizeof(char));
	if (strret == NULL)
	{
		return (free_array((char ***)&strarr), NULL);
	}
	while (*line)
	{
		if (*line == '$')
		{
			i += heredoc_copy_variable(strret + i, strarr[j]);
			line += heredoc_variable_length(line + 1) + 1;
			j++;
		}
		else
		{
			line = heredoc_copy_line(strret + i, line);
			i = ft_strlen(strret);
		}
	}
	return (strret);
}

/**
 * @brief Expand all variables found in @p `line`.
 *
 * @param[in] envp Linked list containing all environmental variables.
 * @param[in] line String read from `readline()`.
 *
 * @retval Pointer to the expanded string if variables are present.
 * @retval Pointer to @p `line`.
 * @retval `NULL` on failure.
 *
 * @warning Caller owns `free()`.
 */
char	*heredoc_expansion(const t_list *envp, const char *line)
{
	const size_t	count = char_count(line, '$');
	size_t			strretlen;
	char			**strarr;
	char			*strret;

	if (count == 0)
	{
		return ((char *)line);
	}
	strarr = heredoc_extract_variables(envp, line);
	if (strarr == NULL)
	{
		return (NULL);
	}
	strret = heredoc_rewrite(line, (const char **)strarr);
	free(line);
	free_array(&strarr);
	return (strret);
}
