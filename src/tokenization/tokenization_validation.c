/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:25:55 by elie              #+#    #+#             */
/*   Updated: 2025/10/18 15:26:19 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: check if inside quotes
bool	validate_token_str(char *str)
{
	size_t	i;
	size_t	count_consecutive;
	uint8_t	curr;
	uint8_t	next;

	i = 0;
	count_consecutive = 0;
	while (str[i])
	{
		curr = get_token_type(&str[i]);
		next = get_token_type(&str[i + 1]);

		if (is_redirection(&str[i]))
		{
			count_consecutive++;

			if (next == TYPE_PIPE)
				return (FAILURE);
			
			// Check if redirection has a target
			if (has_redirection_target(&str[i]) == false)
				return (FAILURE);

			// Check if the there's a mismatch in symbols. i.e.: >< or <> 
			if (get_redirection_type(&str[i + 1]) && curr != next)
				return (FAILURE);

			// Check if there's three redirection tokens in a row
			if (count_consecutive == 3)
				return (FAILURE);
		}
		else if (curr == TYPE_PIPE && has_redirection_target(&str[i]) == false)
			return (FAILURE);
		else
			count_consecutive = 0;

		i++;
	}
	return (SUCCESS);
}

/**
*	@brief Checks whether the current redirection has a target (i.e. in or outfile to redirect to)
*/
bool	has_redirection_target(char *str)
{
	size_t	i;

	i = 1;
	// Skip the redirection token(s)
	while (str[i] && is_redirection(&str[i]))
		i++;
	// Skip whitespace
	while (str[i] && ft_isspace(str[i]))
		i++;
	
	if (str[i] && (get_redirection_type(&str[i]) == 0 && get_token_type(&str[i]) != TYPE_PIPE))
		return (true);
	return (false);
}

bool	validate_quotation(char *str)
{
	char	quote_type;
	size_t	i;
	size_t	count;

	quote_type = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote_type = str[i];
			count++;
			i++;
			while (str[i] && str[i] != quote_type)
				i++;
			if (str[i] == quote_type)
			{
				count++;
				quote_type = 0;
			}
		}
		i++;
	}
	// Return success if even amount of unquoted quotes
	if (count % 2 == 0)
		return (SUCCESS);
	return (FAILURE);
}