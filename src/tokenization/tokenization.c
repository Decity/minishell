/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:20:17 by elie              #+#    #+#             */
/*   Updated: 2025/10/22 17:28:31 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sets tokens from str @p `data->input` to array @p `data->tokens`
 *
 * Example:
 * - in: data->input: 'echo "hello" ${TERM} > test.txt'
 * - out: Tokenized array: ["echo", "\"hello\"", "${TERM}", ">", "test.txt"]
 */
size_t	set_tokens(t_data *data)
{
	size_t	token_count;
	char	*normalized_token_str;

	if (DEBUG)
		printf("=== set_tokens ===\n\n");

	// Validate quoation
	if (validate_quotation(data->input) == FAILURE)
	{
		printf("== Validating quotation: FAILED\n");
		return (FAILURE);
	}

	// validate syntax
	if (validate_token_str(data->input) == FAILURE)
	{
		printf("== validate_token_str: FAILED\n");
		return (FAILURE);
	}

	// Normalize string for easier splittin
	if (DEBUG)
		printf("== Normalizing str [%s]\n", data->input);
	normalized_token_str = normalize_whitespace(data->input);
	ft_repoint(&data->input, normalized_token_str);
	if (DEBUG)
		printf("= After normalizing: [%s] str_len: %lu\n", data->input, ft_strlen(data->input));

	token_count = count_tokens(normalized_token_str);
	data->tokens = ft_calloc((token_count + 1), sizeof(char *));
	tokenize(data, token_count);

	if (DEBUG)
		printf("=== +++ ===\n\n");
	return (SUCCESS);
}

/**
 * @brief Breaks down the string @p `data->input` into an array of tokens.
 */
void	tokenize(t_data *data, size_t token_count)
{
	size_t		i;
	size_t		start;
	size_t		end;
	char		quote;
	const char	*input = data->input;

	i = 0;
	start = 0;
	while (i < token_count)
	{
		while (ft_isspace(input[start]))
			start++;
		end = start;
		// Skip through the token until we hit a space or end of string
		while (input[end] && !ft_isspace(input[end]))
		{
			quote = get_quote(input[end]);
			if (quote)
			{
				end++;
				while (input[end] && input[end] != quote)
					end++;
				if (input[end] == quote)
					end++;
			}
			else
				end++;
		}

		data->tokens[i] = ft_strndup(&input[start], end - start);
		// TODO: malloc check

		start = end;
		i++;
	}
	data->tokens[i] = NULL;
}

/**
 * @brief Counts and returns the amount of tokens the given string @p `input` should be split into
 */
size_t	count_tokens(char *input)
{
	size_t	i;
	char	quote;
	size_t	token_count;

	quote = 0;
	token_count = 1;
	i = 0;
	while (ft_isspace(input[i]))
		i++;
	while (input[i])
	{

		quote = get_quote(input[i]);

		if (quote)
		{
			i++;
			while (input[i] != quote)
				i++;
			quote = 0;
		}
		else if (input[i] && ft_isspace(input[i]))
		{
			while (input[i + 1] && ft_isspace(input[i + 1]))
				i++;
			if (input[i + 1] && !ft_isspace(input[i + 1]))
				token_count++;
		}
		i++;

	}
	if (DEBUG)
		printf("Token count: %lu\n", token_count);
	return (token_count);
}
