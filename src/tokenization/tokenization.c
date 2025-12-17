/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:20:17 by elie              #+#    #+#             */
/*   Updated: 2025/12/17 13:55:39 by dbakker          ###   ########.fr       */
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
	char	*old_input;

	if (validate_quotation(data->input) == FAILURE)
	{
		ft_putendl_fd("minishell: failed to validate quotes.", STDERR_FILENO);
		return (data->exit_status = 2, FAILURE);
	}
	if (validate_token_str(data->input) == FAILURE)
	{
		ft_putendl_fd("minishell: failed to valdiate syntax", STDERR_FILENO);
		return (data->exit_status = 2, FAILURE);
	}
	old_input = data->input;
	data->input = normalize_whitespace(data->input);
	free(old_input);
	if (!data->input)
		exit_cleanup(data, data->exit_status);
	token_count = count_tokens(data->input);
	data->tokens = ft_calloc((token_count + 1), sizeof(char *));
	if (!data->tokens)
		exit_cleanup(data, data->exit_status);
	tokenize(data, token_count);
	return (SUCCESS);
}

static void	tokenization_quote_matching(const char *input, size_t *end,
	char *quote)
{
	while (input[*end] && !ft_isspace(input[*end]))
	{
		*quote = get_quote(input[*end]);
		if (*quote)
		{
			(*end)++;
			while (input[*end] && input[*end] != *quote)
				(*end)++;
			if (input[*end] == *quote)
				(*end)++;
		}
		else
			(*end)++;
	}
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
		while (input[start] && ft_isspace(input[start]))
			start++;
		end = start;
		tokenization_quote_matching(input, &end, &quote);
		data->tokens[i] = ft_strndup(&input[start], end - start);
		if (data->tokens[i] == NULL)
		{
			perror("minishell");
			exit_cleanup(data, i);
		}
		start = end;
		i++;
	}
	data->tokens[i] = NULL;
}

static void	tokenization_quote_handling(char *input, size_t *token_count)
{
	size_t	i;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	while (input[i])
	{
		skip_quoted_section(input, &i);
		if (input[i] && ft_isspace(input[i]))
		{
			while (input[i + 1] && ft_isspace(input[i + 1]))
				i++;
			if (input[i + 1] && !ft_isspace(input[i + 1]))
				(*token_count)++;
		}
		if (input[i])
			i++;
	}
}

/**
 * @brief Counts and returns the amount of tokens the given string
 * @brief @p `input` should be split into.
 */
size_t	count_tokens(char *input)
{
	size_t	token_count;

	token_count = 1;
	tokenization_quote_handling(input, &token_count);
	return (token_count);
}
