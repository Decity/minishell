/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_normalization_strlen.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:31:42 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/08 15:53:55 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenization_in_quote(const char *str, int8_t curr_type,
	int8_t next_type)
{
	uint8_t	is_redir_curr;
	uint8_t	is_redir_next;

	is_redir_curr = get_redirection_type(str - 1);
	is_redir_next = get_redirection_type(str);
	if ((curr_type == TYPE_ARG || curr_type == TYPE_SQUOTE
			|| curr_type == TYPE_DQUOTE)
		&& (next_type == TYPE_PIPE || is_redir_next))
		return (1);
	if ((curr_type == TYPE_PIPE || is_redir_curr)
		&& (next_type == TYPE_ARG || next_type == TYPE_SQUOTE
			|| next_type == TYPE_DQUOTE))
		return (1);
	if (curr_type == TYPE_PIPE && is_redir_next)
		return (1);
	return (0);
}

static void	update_quote_state(const char *str, size_t i, int8_t curr,
	char *in_quote)
{
	if (!*in_quote && (curr == TYPE_SQUOTE || curr == TYPE_DQUOTE))
		*in_quote = str[i - 1];
	else if (*in_quote && str[i - 1] == *in_quote)
		*in_quote = 0;
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
		len++;
		i++;
		update_quote_state(str, i, curr, &in_quote);
		if (curr == TYPE_REDIRECTION_APPEND || curr == TYPE_REDIRECTION_HEREDOC)
		{
			len++;
			i++;
			next = get_token_type(&str[i]);
		}
		if (in_quote == 0)
			len += tokenization_in_quote(str + i, curr, next);
	}
	return (len);
}
