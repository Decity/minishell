/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_normalization.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:18:05 by elie              #+#    #+#             */
/*   Updated: 2025/12/08 16:28:58 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenization_in_quote(const char *str, int8_t curr,
	int8_t next)
{
	uint8_t	is_redir_curr;
	uint8_t	is_redir_next;

	is_redir_curr = get_redirection_type(str - 1);
	is_redir_next = get_redirection_type(str);
	if ((curr == TYPE_ARG || curr == TYPE_SQUOTE || curr == TYPE_DQUOTE)
		&& (next == TYPE_PIPE || is_redir_next))
		return (' ');
	if ((curr == TYPE_PIPE || is_redir_curr)
		&& (next == TYPE_ARG || next == TYPE_SQUOTE || next == TYPE_DQUOTE))
		return (' ');
	if (curr == TYPE_PIPE && is_redir_next)
		return (' ');
	return (0);
}

void	tokenization_normalize(char *new_str, const char *str)
{
	char	in_quote;
	int8_t	curr;
	int8_t	next;
	size_t	i;
	size_t	j;

	in_quote = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		tokenization_update_tokens(str + i, &curr, &next);
		new_str[j++] = str[i++];
		if (!in_quote && (curr == TYPE_SQUOTE || curr == TYPE_DQUOTE))
			in_quote = str[i - 1];
		else if (in_quote && str[i - 1] == in_quote)
			in_quote = 0;
		if (curr == TYPE_REDIRECTION_APPEND || curr == TYPE_REDIRECTION_HEREDOC)
		{
			new_str[j++] = str[i++];
			next = get_token_type(&str[i]);
		}
		if (in_quote == 0 && tokenization_in_quote(str + i, curr, next))
			new_str[j++] = tokenization_in_quote(str + i, curr, next);
	}
}

/**
 * @brief Returns a str with guaranteed whitespace around redirections and pipes
 */
char	*normalize_whitespace(const char *str)
{
	char	*new_str;

	new_str = ft_calloc(get_normalized_str_len(str) + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	tokenization_normalize(new_str, str);
	return (new_str);
}
