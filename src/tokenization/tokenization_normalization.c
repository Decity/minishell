/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_normalization.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:18:05 by elie              #+#    #+#             */
/*   Updated: 2025/10/20 12:22:51 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: fix disrepency get_normalized_strlen
// Input: "echo "hi"|cat|grep "h""
// Tokens: [echo, "hi", |, cat, |, grep, "h"AU]

// Input:  echo "hi"|cat|grep "h"
// Tokens: [echo, "hi", |, cat, |, grep, "h"V]

// Input:  echo 'hi'|cat|grep 'h'
// Tokens: [echo, 'hi', |, cat, |, grep, 'h'V]

size_t	get_normalized_str_len(const char *str)
{
	size_t	len;
	size_t	i;
	int8_t	curr_type;
	int8_t	next_type;
	char	in_quote;

	i = 0;
	len = 0;
	in_quote = 0;
	while (str[i])
	{
		curr_type = get_token_type(&str[i]);
		next_type = get_token_type(&str[i + 1]);

		// Normalize if not in quotes
		if (!in_quote && curr_type != TYPE_SQUOTE && curr_type != TYPE_DQUOTE)
		{
			// Add space between arg and pipe/redirect
			if (curr_type == TYPE_ARG && (next_type == TYPE_PIPE || get_redirection_type(&str[i + 1])))
				len++;
			// Add space between pipe/redirect and arg
			if ((curr_type == TYPE_PIPE || get_redirection_type(&str[i])) && next_type == TYPE_ARG)
				len++;
		}

		// Track quoatation
		if (!in_quote && (curr_type == TYPE_SQUOTE || curr_type == TYPE_DQUOTE))
			in_quote = str[i];
		else if (in_quote && str[i] == in_quote)
			in_quote = 0;

		// Handle double-char tokens
		if (curr_type == TYPE_REDIRECTION_APPEND || curr_type == TYPE_REDIRECTION_HEREDOC)
		{
			len += 2;
			i++;
		}
		else
			len++;
		i++;
	}
	if (DEBUG)
		printf("== normalized str len = %lu\n", len);
	return (len);
}

char	*normalize_whitespace(const char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	int8_t	curr_type;
	int8_t	next_type;
	char	in_quote;

	new_str = ft_calloc(get_normalized_str_len(str) + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);

	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		curr_type = get_token_type(&str[i]);
		next_type = get_token_type(&str[i + 1]);

		new_str[j++] = str[i++];

		// Handle >> and <<
		if (curr_type == TYPE_REDIRECTION_APPEND || curr_type == TYPE_REDIRECTION_HEREDOC)
		{
			new_str[j++] = str[i++];
			next_type = get_token_type(&str[i]);
		}

		// track quotation
		if (!in_quote && (curr_type == TYPE_SQUOTE || curr_type == TYPE_DQUOTE))
			in_quote = str[i - 1];
		else if (in_quote && str[i - 1] == in_quote)
			in_quote = 0;

		if (!in_quote)
		{
			// Add space between an arg and pipe/redirect
			if (curr_type == TYPE_ARG && (next_type == TYPE_PIPE || get_redirection_type(&str[i])))
				new_str[j++] = ' ';
			// Add space between pipe/redirect and an arg
			else if ((curr_type == TYPE_PIPE || get_redirection_type(&str[i - 1])) && next_type == TYPE_ARG)
				new_str[j++] = ' ';
			// Add space between pipe and redirection
			else if (curr_type == TYPE_PIPE && get_redirection_type(&str[i]))
				new_str[j++] = ' ';
			// Add space between closing quote and pipe/redirect
			else if ((curr_type == TYPE_SQUOTE || curr_type == TYPE_DQUOTE) && (next_type == TYPE_PIPE || get_redirection_type(&str[i])))
				new_str[j++] = ' ';
			// Add space between pipe/redirect if next is quote
			else if ((curr_type == TYPE_PIPE || get_redirection_type(&str[i - 1])) && (next_type == TYPE_SQUOTE || next_type == TYPE_DQUOTE))
				new_str[j++] = ' ';
		}
	}
	return (new_str);
}
