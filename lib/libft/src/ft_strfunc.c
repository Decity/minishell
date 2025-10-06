/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:42:31 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Apply function @p func to each character of @p str.
 *
 * @param[in,out]	str		String to iterate.
 * @param[in]		func	Function to apply to each character.
 */
void	ft_striteri(char *str, void (*func)(unsigned int, char*))
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
 * @brief	Apply function @p func to each character of @p str.
 *
 * @param[in]	str		String to iterate.
 * @param[in]	func	Function to apply to each character.
 *
 * @returns	The pointer to the new string from the successive applications of
 * 			@p func, or NULL on Failure.
 *
 * @warning	The caller owns free() when done.
 */
char	*ft_strmapi(char const *str, char (*func)(unsigned int, char))
{
	char	*ptr;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = func(i, str[i]);
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}
