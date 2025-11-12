/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/12 15:53:17 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return The amount of heredoc redirections found across all command structs.
 */
size_t	count_heredocs(t_cmd *cmd)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (cmd)
	{
		while (cmd->redirect.infile[i].file)
		{
			if (cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				count++;
			}
			i++;
		}
		i = 0;
		cmd = cmd->next;
	}
	return (count);
}

/**
 * @return A generated array of strings to be used as names for the heredoc
 * @return files, or `NULL` on failure.
 */
char	**generate_heredoc_names(size_t count)
{
	const char	hex[] = HEX_UPPER;
	char		**names;
	char		number[2];
	size_t		i;

	names = ft_calloc(count + 1, sizeof(char *));
	if (names == NULL)
	{
		return (NULL);
	}
	ft_memset(number, 0, sizeof(number));
	i = 0;
	while (i < count)
	{
		number[0] = hex[i % BASE_16];
		names[i] = ft_strjoin("/tmp/heredoc_", number);
		if (names[i] == NULL)
		{
			return (ft_free2d((void **)names, i), NULL);
		}
		i++;
	}
	return (names);
}

void	heredoc(t_cmd *cmd)
{
	const size_t	count = count_heredocs(cmd);
	char			**names;
	size_t			i;

	if (count > 16)
	{
		return ;
	}
	names = generate_heredoc_names(count);
	if (names == NULL)
	{
		return ;
	}
	i = 0;
	while (i < count)
	{
		open(names[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		i++;
	}
}
