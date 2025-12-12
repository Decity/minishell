/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_normalization_strlen.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:31:42 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/12 16:13:52 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenization_in_quote_heredoc(const char *str, int8_t curr_type,
	int8_t next_type);
int	tokenization_in_quote_append(const char *str, int8_t curr_type,
	int8_t next_type);
int	tokenization_in_quote_redirect_out(const char *str, int8_t curr_type,
	int8_t next_type);
int	tokenization_in_quote_redirect_in(const char *str, int8_t curr_type,
	int8_t next_type);
int	tokenization_in_quote_pipe(const char *str, int8_t curr_type,
	int8_t next_type);

static int	tokenization_in_quote(const char *str, int8_t curr_type,
	int8_t next_type)
{
	if (tokenization_in_quote_pipe(str, curr_type, next_type)
		|| tokenization_in_quote_redirect_in(str, curr_type, next_type)
		|| tokenization_in_quote_redirect_out(str, curr_type, next_type))
	{
		return (1);
	}
	if (tokenization_in_quote_append(str, curr_type, next_type)
		|| tokenization_in_quote_heredoc(str, curr_type, next_type))
	{
		return (2);
	}
	return (0);
}

static uint8_t	tokenization_append_heredoc(const char *str, size_t *i,
	size_t *len)
{
	*len += 2;
	*i += 1;
	return (get_token_type(str));
}

/**
 * @brief calculates the len for the normalized version of the given str
 */
size_t	get_normalized_str_len(const char *str)
{
	size_t	len;
	size_t	i;
	int8_t	curr;
	int8_t	next;
	char	in_quote;

	i = 0;
	len = 0;
	in_quote = 0;
	while (str[i])
	{
		tokenization_update_tokens(str + i, &curr, &next);
		if (!in_quote && (curr == TYPE_SQUOTE || curr == TYPE_DQUOTE))
			in_quote = str[i];
		else if (in_quote && str[i] == in_quote)
			in_quote = 0;
		if (curr == TYPE_REDIRECTION_APPEND || curr == TYPE_REDIRECTION_HEREDOC)
			next = tokenization_append_heredoc(str + i + 1, &i, &len);
		else
			len++;
		i++;
		if (in_quote == 0)
			len += tokenization_in_quote(str + i, curr, next);
	}
	return (len);
}
