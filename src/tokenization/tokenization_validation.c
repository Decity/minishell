/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:25:55 by elie              #+#    #+#             */
/*   Updated: 2025/12/10 08:35:54 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether the current redirection has a target
 * @brief (i.e. in or outfile to redirect to).
*/
bool	has_redirection_target(char *str)
{
	size_t	i;

	i = 1;
	while (str[i] && is_redirection(&str[i]))
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[0] == '|' && str[i] && str[i] != '|')
		return (true);
	if (str[i] && (get_redirection_type(&str[i]) == 0
			&& get_token_type(&str[i]) != TYPE_PIPE))
		return (true);
	printf("= %c has no target\n", str[i]);
	return (false);
}

/**
 * @brief Checks if there's an even amount of quotes, not counting quoted
 * @brief quotes.
 */
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
		if (get_quote(str[i]))
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
		if (str[i])
			i++;
	}
	return ((count + 1) % 2);
}
