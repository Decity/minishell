/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/25 15:57:07 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Closes and unlinks all generated files for the heredocs.
 */
void	remove_heredoc_files(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd)
	{
		while (cmd->redirect.infile[i].file)
		{
			if (cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				close(cmd->redirect.infile[i].fd);
				unlink(cmd->redirect.infile[i].file);
			}
			i++;
		}
		i = 0;
		cmd = cmd->next;
	}
}

/**
 * @brief Initializes all command structs with a file for the heredoc to write
 * @brief to.
 *
 * @param[out] cmd Command struct to initialize.
 *
 * @return Pointer to @p `cmd`, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
void	*init_heredoc(t_cmd *cmd)
{
	t_cmd	*node;
	size_t	i;

	i = 0;
	node = cmd;
	while (node)
	{
		while (node->redirect.infile[i].file || node->redirect.infile[i].delimiter)
		{
			if (node->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				node->redirect.infile[i].file = generate_heredoc_name();
				if (node->redirect.infile[i].file == NULL)
				{
					return (NULL);
				}
			}
			i++;
		}
		i = 0;
		node = node->next;
	}
	return (cmd);
}

/**
 * The warning it prints out if you CTRL + D in the heredoc.
 */
void	heredoc_print_warning(size_t line_count, const char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnum_fd(line_count, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

bool	heredoc_check(t_data *data)
{
	if (count_redir_heredoc((const char **)data->tokens) > HEREDOC_LIMIT)
	{
		return (false);
	}
	if (init_heredoc(data->command) == NULL)
	{
		return (false);
	}
	return (true);
}

// /**
//  * @brief Return a new pointer of @p `str` after the first `$` sign.
//  *
//  * The length of the string will be delimited by ft_isspace() and get_quote().
//  *
//  * @param[in] str The string at which to extract the first variable.
//  *
//  * @return Pointer to the new string, or `NULL` on failure.
//  *
//  * @warning Caller owns free().
//  */
// char	*extract_variable(const char *str)
// {
// 	char	*envvar;
// 	size_t	namelen;

// 	envvar = ft_strchr(str, '$');
// 	if (envvar == NULL)
// 	{
// 		return (NULL);
// 	}
// 	while (envvar[namelen + 1] && ft_isspace(envvar[namelen + 1]) == false && get_quote(envvar[namelen + 1]) == false)
// 	{
// 		namelen += 1;
// 	}
// 	envvar = ft_strndup(ft_strchr(str, '$') + 1, namelen);
// 	if (envvar == NULL)
// 	{
// 		return (NULL);
// 	}
// 	return (envvar);
// }

/**
 * @return The length of @p `line` until it encounters a `ft_isspace()`,
 * @return `get_quote()` or a `$` character.
 */
size_t	heredoc_variable_length(const char *line)
{
	size_t	length;

	length = 0;
	while (line[length] && ft_isspace(line[length]) == false
	&& get_quote(line[length]) == false && line[length] != '$')
	{
		length += 1;
	}
	return (length);
}

/**
 * @return The amount of times @p `chr` appears in @p `str`.
 */
size_t	char_count(const char *str, int chr)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == chr)
		{
			count += 1;
		}
		i += 1;
	}
	return (count);
}

/**
 * @return The combined length of all strings in @p `strarr`.
 */
size_t	strarrlen(const char **strarr)
{
	size_t	length;
	size_t	i;
	size_t	j;

	length = 0;
	i = 0;
	j = 0;
	while (strarr[i])
	{
		while (strarr[i][j])
		{
			length += 1;
			j += 1;
		}
		j = 0;
		i += 1;
	}
	return (length);
}

/**
 * @brief Count how many variables are in @p `line` and store each one in an
 * @brief array.
 *
 * Anything after a `$` is considered a variable.
 *
 * @param[in] line Returned string from `readline()`.
 *
 * @return Pointer to the array of variables found in @p `line`, or `NULL` on
 * @return failure.
 *
 * @warning Caller owns `free()`.
 */
char	**extract_variables(const char *line)
{
	char	**strarr;
	char	*dollar;
	size_t	num;
	size_t	count;
	size_t	i;

	count = char_count(line, '$');
	strarr = ft_calloc(count + 1, sizeof(char *));
	if (strarr == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dollar = ft_strchr(line, '$') + 1;
		num = heredoc_variable_length(dollar);
		if (num == 0)
			strarr[i] = ft_strdup("$");
		else
			strarr[i] = ft_strndup(dollar, num);
		if (strarr[i] == NULL)
			return (free_array(&strarr), NULL);
		line = dollar;
		i += 1;
	}
	return (strarr);
}

// char	*heredoc_expansion(t_list *envp, const char *line)
// {
// 	char	**strarr;
// 	char	*str;
// 	char	*envvalue;
// 	size_t	count;
// 	size_t	len;
// 	size_t	strslen;
// 	size_t	i;
// 	size_t	j;

// 	count = char_count(line, '$');
// 	if (count == 0)
// 	{
// 		return (line);
// 	}
// 	strarr = extract_variables(line);
// 	if (strarr == NULL)
// 	{
// 		return (NULL);
// 	}
// 	strslen = strarrlen((const char **)strarr);
// 	len = ft_strlen(line);
// 	str = ft_calloc(len + strslen + 1, sizeof(char));
// 	if (str == NULL)
// 	{
// 		return (free_array(&strarr), NULL);
// 	}
// 	i = 0;
// 	j = 0;
// 	while (i < len + strslen)
// 	{
// 		while (line[i] && line[i] != '$')
// 		{
// 			str[i] = line[i];
// 			i += 1;
// 		}
// 		if (line[i] == '\0')
// 		{
// 			break ;
// 		}
// 		envvalue = ft_getenv(envp, strarr[j]);
// 		ft_memcpy(str + i, strarr[j], ft_strlen(strarr[j]));
// 		i += ft_strlen(strarr[j]);
// 		j += 1;
// 	}
// 	return (str);
// }

// char	*expand_variable(t_list *envp, char *str)
// {
// 	size_t	namelen;
// 	size_t	new_strlen;
// 	size_t	i;
// 	size_t	j;
// 	char	*envvar;
// 	char	*envvalue;
// 	char	*new_str;

// 	namelen = 0;
// 	envvar = extract_variable(str, &namelen);
// 	if (envvar == NULL)
// 	{
// 		return (NULL);
// 	}
// 	envvalue = ft_getenv(envp, envvar);
// 	free(envvar);
// 	if (envvalue == NULL)
// 	{
// 		return (NULL);
// 	}
// 	new_strlen = ft_strlen(str) - namelen + ft_strlen(envvalue);
// 	new_str = ft_calloc(new_strlen + 1, sizeof(char));
// 	if (new_str == NULL)
// 	{
// 		return (NULL);
// 	}
// 	i = 0;
// 	j = 0;
// 	while (i < new_strlen)
// 	{
// 		while (str[j] && str[j] != '$')
// 		{
// 			new_str[i] = str[j];
// 			i++;
// 			j++;
// 		}
// 		if (str[j] == '\0')
// 		{
// 			break ;
// 		}
// 		ft_memcpy(new_str + i, envvalue, ft_strlen(envvalue));
// 		i += ft_strlen(envvalue);
// 		j += namelen + 1;
// 	}
// 	return (new_str);
// }

void	heredoc_readline(t_cmd *cmd, t_list *envp, size_t i)
{
	static size_t	line_count = 0;
	char			*line;
	char			*expand;

	while (true != false)
	{
		line = readline(NULL);
		line_count++;
		if (line == NULL)
		{
			heredoc_print_warning(line_count, cmd->redirect.infile[i].delimiter);
			break ;
		}
		if (strcmp(line, cmd->redirect.infile[i].delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, cmd->redirect.infile[i].fd);
		free(line);
	}
}

void	*heredoc_file_insertion(t_cmd *cmd, t_list *envp)
{
	size_t			i;

	i = 0;
	while (cmd->redirect.infile[i].file)
	{
		if (cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
		{
			cmd->redirect.infile[i].fd = open(cmd->redirect.infile[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->redirect.infile[i].fd == -1)
				return (NULL);
			heredoc_readline(cmd, envp, i);
			close(cmd->redirect.infile[i].fd);
		}
		i++;
	}
	return (cmd);
}

t_data	*heredoc(t_data *data)
{
	t_cmd	*cmd;
	if (DEBUG)
		printf("=== Heredoc begin ===\n");

	if (heredoc_check(data) == false)
		return (NULL);

	cmd = data->command;
	while (cmd)
	{
		heredoc_file_insertion(cmd, data->envp);
		cmd = cmd->next;
	}
	if (DEBUG)
		printf("=== Heredoc end ===\n");
	return (data);
}
