/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:38:07 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 17:17:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Returns a new string from concatenating @p str1 and @p str2.
 *
 * @param[in]	str1	The prefix string.
 * @param[in]	str2	The suffix string.
 *
 * @returns	Pointer to the new string, or NULL on failure.
 *
 * @warning	The caller owns free() when done.
 */
char	*ft_strjoin(const char *dest, const char* src)
{
	char	*str;
	size_t	srclen;
	size_t	destlen;

	if (dest == NULL || src == NULL)
	{
		return (NULL);
	}
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src) + 1;
	str = ft_calloc(destlen + srclen, sizeof(char));
	if (str == NULL)
	{
		return (NULL);
	}
	ft_memcpy(str, dest, destlen);
	ft_memcpy(str + destlen, src, srclen);
	return (str);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	unsigned int	len;
// 	unsigned int	i;
// 	unsigned int	j;
// 	char			*str;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	str = ft_calloc((len + 1), sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		str[i + j] = s2[j];
// 		j++;
// 	}
// 	str[i + j] = '\0';
// 	return (str);
// }
