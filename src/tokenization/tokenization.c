/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:20:17 by elie              #+#    #+#             */
/*   Updated: 2025/10/18 15:19:52 by elie             ###   ########.fr       */
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
int	set_tokens(t_data *data)
{
	int		token_count;
	char	*normalized_token_str;

	if (DEBUG)
		printf("=== set_tokens ===\n\n");

	// Validate quoation
	if (validate_quotation(data->input) == FAILURE)
	{
		printf("== Validating quotation:\n = FAILED\n");
		return (FAILURE);
	}

	// validate syntax
	if (validate_token_str(data->input) == FAILURE)
	{
		printf("== validate_token_str:\n = FAILED\n");
		return (FAILURE);
	}

	// Normalize string for easier splittin
	if (DEBUG)
		printf("== Normalizing str\n"), printf("= before: %s\n", data->input);
	normalized_token_str = normalize_whitespace(data->input);
	ft_repoint(&data->input, normalized_token_str);
	if (DEBUG)
		printf("= After normalizing: %s\n", data->input);

	token_count = count_tokens(normalized_token_str);
	data->tokens = ft_calloc((token_count + 1), sizeof(char *));
	tokenize(data, token_count);

	return (SUCCESS);
	if (DEBUG)
		printf("=== +++ ===\n\n");
}

/**
 * @brief Breaks down the string @p `data->input` into an array of tokens.
 */
void	tokenize(t_data *data, int token_count)
{
	int		i;
	int		start;
	int		end;
	char	quote;

	const char *input = data->input;

	i = 0;
	start = 0;
	quote = 0;
	while (i < token_count)
	{
		// Skip whitespace
		while(ft_isspace(input[start]) == true)
			start++;

		end = start;
		if (is_quote(input[end]) == true)
		{
			while (is_quote(input[end]) == true)
			{
				quote = input[end];
				end++;
				while (input[end] && input[end] != quote)
					end++;
				end++;
			}
		}
		else if (input[end])
		{
			while (input[end] && ft_isspace(input[end]) == false)
				end++;
		}
		// Duplicate str from start to end
		data->tokens[i] = ft_strndup(&input[start], end - start);
		// TODO: malloc check

		i++;
		start = end;
	}
	data->tokens[i] = NULL;

}

/**
 * @brief Counts and returns the amount of tokens the given string @p `input` should be split into
 */
int		count_tokens(char *input)
{
	int		i;
	char	quote;
	int		token_count;

	quote = 0;
	token_count = 0;
	i = 0;
	while (input[i])
	{
		// Skip whitespace
		while (ft_isspace(input[i]) == true)
			i++;

		if (!input[i])
			break ;

		// Check for quote or non quote
		if (is_quote(input[i]) == true)
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			i++;
		}
		else
		{
			while (input[i] && ft_isspace(input[i]) == false)
				i++;
		}
		token_count++;
	}
	if (DEBUG)
		printf("Token count: %i\n", token_count);
	return (token_count);
}
