/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_normalization_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:43:17 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/17 13:56:54 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenization_update_tokens(const char *str, int8_t *curr_type,
	int8_t *next_type)
{
	*curr_type = (int8_t)get_token_type(str);
	*next_type = (int8_t)get_token_type(str + 1);
}

void	skip_quoted_section(char *input, size_t *i)
{
	char	quote;

	quote = get_quote(input[*i]);
	if (quote)
	{
		(*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
	}
}
