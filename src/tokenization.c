/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:20:17 by elie              #+#    #+#             */
/*   Updated: 2025/10/03 16:17:18 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Breaks the input into words and operators, obeying the quoting rules described in Quoting.
// These tokens are separated by metacharacters. This step performs alias expansion (see Aliases)

// TODO: Implement proper tokenization of operators. Currently they're considered part of strings
// when theres no whitespace betwen the operator and the rest of the str

/**
 * @brief Sets tokens from @p `data->input` to @p `data->tokens`
 *
 * Example:
 * - in: data->input: 'echo "hello" ${TERM} > test.txt'
 * - out: Tokenized array: ["echo", "\"hello\"", "${TERM}", ">", "test.txt"]
 */
void	set_tokens(t_data *data)
{
	int	token_count;

	if (DEBUG)
		printf("=== set_tokens ===\n\n");

	// TODO: validate_input_for_tokenization(data->input);
	token_count = count_tokens(data->input);
	data->tokens = ft_calloc((token_count + 1), sizeof(char *));
	tokenize(data, token_count);

	if (DEBUG)
		printf("=== +++ ===\n\n");
}

/**
 * @brief Breaks down the string @p `data->input` into an array of tokens.
 */
void	tokenize(t_data *data, int token_count)
{
	int	i;
	int	start;
	int	end;
	int	quote;

	const char *input = data->input;

	i = 0;
	start = 0;
	quote = 0;
	while (i < token_count)
	{
		// Skip whitespace
		while(is_whitespace(input[start]) == true)
			start++;

		end = start;
		if (is_quote(input[end]) == true)
		{
			quote = input[end];
			end++;
			while (input[end] && input[end] != quote)
				end++;
			end++;
		}
		else if (input[end])
		{
			while (input[end] && is_whitespace(input[end]) == false)
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

bool	is_quote(int c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

/**
 * @brief Counts and returns the amount of tokens the given string @p `input` should be split into
 */
int		count_tokens(char *input)
{
	int	i;
	int	quote;
	int	token_count;

	quote = 0;
	token_count = 0;
	i = 0;
	while (input[i])
	{
		// Skip whitespace
		while (is_whitespace(input[i]) == true)
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
			token_count++;
		}
		else
		{
			token_count++;
			while (input[i] && is_whitespace(input[i]) == false)
				i++;
		}
	}
	if (DEBUG)
		printf("Token count: %i\n", token_count);
	return (token_count);
}


