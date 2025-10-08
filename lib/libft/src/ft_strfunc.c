/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:42:31 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/08 22:11:18 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Apply @p `func` to each character of @p `str`.
 *
 * @param[in,out]	str		String to iterate.
 * @param[in]		func	Function to apply to each character.
 */
void	ft_striteri(char *str, void (*func)(uint32_t, char*))
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		func(i, &str[i]);
		i++;
	}
}

/**
 * @brief Apply @p `func` to each character of @p `str`.
 *
 * @param[in]	str		String to iterate.
 * @param[in]	func	Function to apply to each character.
 *
 * @return The pointer to the new string from the successive applications of
 * @return @p `func`, or `NULL` on failure.
 *
 * @warning	Caller owns free().
 */
char	*ft_strmapi(const char *str, char (*func)(uint32_t, char))
{
	char	*ptr;
	size_t	i;
	size_t	strlen;

	i = 0;
	strlen = ft_strlen(str);
	ptr = ft_calloc(strlen + 1, sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	while (i < strlen)
	{
		ptr[i] = func(i, str[i]);
		i++;
	}
	return (ptr);
}
