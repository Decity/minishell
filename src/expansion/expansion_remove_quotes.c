/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_remove_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:11:34 by elie              #+#    #+#             */
/*   Updated: 2025/12/03 20:03:10 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new string with the most outer quotes removed.
 *
 * @param[in] str String containing closed quotes.
 *
 * @return A pointer with the outer quotes from @p `str` removed.
 *
 * @warning Caller owns `free()`.
 */
char	*expansion_remove_quotation(char *str)
{
	char	*strret;
	size_t	i;
	size_t	j;
	char	quote;

	if (str == NULL)
	{
		return (NULL);
	}
	strret = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (strret == NULL)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			i++;
			continue;
		}
		else if (quote != 0 && str[i] == quote)
		{
			quote = 0;
			i++;
			continue;
		}
		strret[j++] = str[i++];
	}
	free(str);
	return (strret);
}
