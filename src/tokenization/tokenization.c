/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:20:17 by elie              #+#    #+#             */
/*   Updated: 2025/12/08 14:53:05 by dbakker          ###   ########.fr       */
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

	if (validate_quotation(data->input) == FAILURE)
	{
		perror("minishell: failed to validate quotes.\n");
		data->exit_status = 2;
		return (FAILURE);
	}
	if (validate_token_str(data->input) == FAILURE)
	{
		printf("minishell: failed to valdiate syntax\n");
		data->exit_status = 2;
		return (FAILURE);
	}
	data->input = normalize_whitespace(data->input);
	if (!data->input)
		exit_cleanup(data, data->exit_status);
	token_count = count_tokens(data->input);
	data->tokens = ft_calloc((token_count + 1), sizeof(char *));
	if (!data->tokens)
		exit_cleanup(data, data->exit_status);
	tokenize(data, token_count);
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
		if (data->tokens[i] == NULL)
			exit_cleanup(data, data->exit_status);
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
	return (token_count);
}
