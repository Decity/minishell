/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/11/13 15:59:05 by dbakker          ###   ########.fr       */
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
 * @brief Generate a pointer of length @p `size` read from `/dev/urandom`.
 *
 * The returning pointer can contain zero bytes, therefore it
 * should not be treated as a null-terminated string.
 *
 * @param[in] size Length of the pointer.
 *
 * @return A string of characters, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
void	*generate_random_pointer(size_t size)
{
	const char	filepath[] = "/dev/urandom";
	int			fd;
	void		*ptr;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		return (NULL);
	}
	ptr = ft_calloc(size, sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	if (read(fd, ptr, size) == -1)
	{
		free(ptr);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (ptr);
}

/**
 * @brief Convert @p `size` bytes of @p `ptr` into a string of hexadecimal characters.
 *
 * Returns `NULL` if @p `ptr` is `NULL`.
 *
 * @param[in] ptr	Pointer to convert to a string of base 16 characters.
 * @param[in] size	Amount of bytes to copy.
 *
 * @return Pointer to the newly allocated string, or `NULL` on failure.
 *
 * @warning Caller owns free().
 */
char	*convert_mem_to_base16(const void *ptr, size_t size)
{
	size_t	i;
	char	*hex_str;

	if (ptr == NULL)
	{
		return (NULL);
	}
	hex_str = ft_calloc(size + 1, sizeof(char));
	if (hex_str == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		hex_str[i] = HEX_LOWER[((uint8_t *)ptr)[i] % BASE_16];
		i++;
	}
	return (hex_str);
}

// /**
//  * @return A generated array of strings to be used as names for the heredoc
//  * @return files, or `NULL` on failure.
//  */
// char	**generate_heredoc_names(size_t count)
// {
// 	const size_t	size = 16;
// 	void			*ptr;
// 	char			**names;
// 	size_t			i;

// 	names = ft_calloc(count + 1, sizeof(char *));
// 	if (names == NULL)
// 	{
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < count)
// 	{
// 		ptr = generate_random_pointer(size);
// 		names[i] = convert_mem_to_base16(ptr, size);
// 		free(ptr);
// 		if (names[i] == NULL)
// 		{
// 			return (ft_free2d((void **)names, i), NULL);
// 		}
// 		i++;
// 	}
// 	return (names);
// }

/**
 * @return Return a randomly generated string of base 16 characters.
 *
 * The length of the string is defined by `HEREDOC_FILENAME_LENGTH`.
 *
 * @warning Caller owns free().
 */
char	*generate_heredoc_name()
{
	char	*filename;
	void	*ptr;

	ptr = generate_random_pointer(HEREDOC_FILENAME_LENGTH);
	filename = convert_mem_to_base16(ptr, HEREDOC_FILENAME_LENGTH);
	free(ptr);
	return (filename);
}

void	assign_heredoc_delimiters(t_hd *hd, t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd)
	{
		while (cmd->redirect.infile[i].file)
		{
			if (cmd->redirect.infile[i].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				hd->delimiter = cmd->redirect.infile[i].file;
			}
			i++;
		}
		i = 0;
		cmd = cmd->next;
	}

}


t_cmd	*init_heredoc(t_cmd *cmd)
{
	const size_t	count = count_heredocs(cmd);
	size_t			i;
	size_t			j;

	if (count > HEREDOC_LIMIT)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < count)
	{
		cmd->heredoc[i].filename = generate_heredoc_name();
		while (cmd->redirect.infile[j].file)
		{
			if (cmd->redirect.infile[j].redir_type == TYPE_REDIRECTION_HEREDOC)
			{
				cmd->heredoc[i].delimiter = cmd->redirect.infile[j].file;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (cmd);
}

void	remove_files(t_cmd *cmd)
{
	size_t	i;
	int		ret_unlink;
	int		ret_close;

	i = 0;
	while (cmd)
	{
		while (cmd->heredoc[i].filename)
		{
			ret_close = close(cmd->heredoc[i].fd);
			ret_unlink = unlink(cmd->heredoc[i].filename);
			i++;
		}
		i = 0;
		cmd = cmd->next;
	}
}

void	heredoc(t_cmd *cmd)
{
	t_hd	*heredoc;
	char	*line;
	size_t	i;

	heredoc->filename = init_heredoc(cmd);
	if (heredoc->filename == NULL)
	{
		return ;
	}
	i = 0;
	while (i)
	{
		heredoc->fd[i] = open(heredoc->filename[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while (1)
		{
			line = readline(NULL);

		}

		i++;
	}
}
