/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/27 15:53:47 by dbakker          ###   ########.fr       */
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

char	*heredoc_duplicate(const char *line)
{
	char	*dollar;
	size_t	num;

	dollar = ft_strchr(line, '$') + 1;
	num = heredoc_variable_length(dollar);
	return (ft_strndup(dollar, num));
}

char	*heredoc_expand(const t_list *envp, const char *envvar)
{
	// TODO: Expand $?
	if (ft_getenv(envp, envvar) == NULL)
	{
		return (ft_strdup(""));
	}
	return (ft_strdup(ft_getenv(envp, envvar)));
}

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
char	**heredoc_extract_variables(const t_list *envp, const char *line)
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

size_t	heredoc_new_strlen(const char **strarr, const char *line)
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

size_t	heredoc_copy_variable(char *strret, const char *src)
{
	const size_t	slen = ft_strlen(src);

	if (slen)
	{
		ft_memcpy(strret, src, slen);
	}
	return (slen);
}

size_t	heredoc_copy_line(char *strret, const char *src)
{
	const char	*envvar = ft_strchr(src, '$');
	size_t		num;

	if (envvar == NULL)
	{
		num = ft_strlen(src);
	}
	else
	{
		num = envvar - src;
	}
	if (num)
	{
		ft_memcpy(strret, src, num);
	}
	if (envvar == NULL)
	{
		src = src + num;
	}
	else
	{
		src = envvar;
	}
	return (src);
}

char	*heredoc_rewrite(const char *line, const char **strarr)
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
	free_array(&strarr);
	return (strret);
}

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
		line = heredoc_expansion(envp, line);
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
