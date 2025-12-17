/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_remove_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:11:34 by elie              #+#    #+#             */
/*   Updated: 2025/12/04 12:13:46 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copy from @p `src` to @p `dest` with outer quotes removed.
 *
 * @param[out]	dest	String to copy to.
 * @param[in]	src		String to copy from.
 *
 * @return Pointer to @p `dest`.
 */
static char	*expansion_copy_woquote(char *dest, char *src)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (quote == 0 && (src[i] == '\'' || src[i] == '\"'))
		{
			quote = src[i];
			i++;
			continue ;
		}
		else if (quote != 0 && src[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		dest[j++] = src[i++];
	}
	return (dest);
}

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

	if (str == NULL)
	{
		return (NULL);
	}
	strret = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (strret == NULL)
	{
		free(str);
		return (NULL);
	}
	expansion_copy_woquote(strret, str);
	return (free(str), strret);
}
