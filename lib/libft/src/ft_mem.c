/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:27:22 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:47:26 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Find the first matching instance of @p c in @p str.
 *
 * @param[in]	str	Memory area to read.
 * @param[in]	c	Instance to find.
 * @param[in]	n	Characters to read in bytes.
 *
 * @returns	Pointer to the matching byte, or NULL if it does not occur.
 */
void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*strp;

	strp = (unsigned char *)str;
	while (n-- > 0)
	{
		if (*strp == (unsigned char)c)
			return (strp);
		strp++;
	}
	return (NULL);
}

/**
 * @brief	Compare the first @p n bytes of the memory areas @p str1 and @p str2.
 *
 * @param[in]	str1	Memory area to compare to @p str2.
 * @param[in]	str2	Memory area to compare to @p str1.
 * @param[in]	n		Characters to read in bytes.
 *
 * @returns	Nonzero value by the sign of the difference between the first pair
 * 			of bytes that differ in @p str1 and @p str2, or 0 if no difference.
 *
 * @retval	0 if @p n is zero, or there is no difference found in @p n bytes.
 * @retval	A positive value if @p str1 is greater than @p str2.
 * @retval	A negative value if @p str1 is less than @p str2.
 */
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*strp1;
	const unsigned char	*strp2;

	strp1 = (const unsigned char *)str1;
	strp2 = (const unsigned char *)str2;
	if (n == 0 || strp1 == strp2)
		return (0);
	while (n-- > 0)
	{
		if (*strp1 != *strp2)
			return (*strp1 - *strp2);
		strp1++;
		strp2++;
	}
	return (0);
}

/**
 * @brief	Copy @p n bytes from memory area @p src to @p dst.
 *
 * @param[out]	dst	Memory area to copy to.
 * @param[in]	src		Memory area to copy from.
 * @param[in]	n		Amount to copy in bytes.
 *
 * @returns	A pointer to @p dst.
 *
 * @note	Use ft_memmove() if areas overlap.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*strsrc;
	unsigned char		*strdst;

	strsrc = (const unsigned char *)src;
	strdst = (unsigned char *)dst;
	while (n--)
		*strdst++ = *strsrc++;
	return (dst);
}

/**
 * @brief	Copy @p n bytes from memory area @p src to @p dst.
 *
 * @param[out]	dst	Memory area to copy to.
 * @param[in]	src		Memory area to copy from.
 * @param[in]	n		Amount to copy in bytes.
 *
 * @returns	A pointer to @p dst.
 */
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char	*strsrc;
	unsigned char		*strdst;

	strsrc = (const unsigned char *)src;
	strdst = (unsigned char *)dst;
	if (strdst == strsrc || n == 0)
		return (dst);
	if (strdst < strsrc)
		ft_memcpy(dst, src, n);
	else
	{
		strdst += n;
		strsrc += n;
		while (n-- > 0)
			*(--strdst) = *(--strsrc);
	}
	return (dst);
}

/**
 * @brief	Fill @p c to the memory area @p str by the first @p n bytes.
 *
 * @param[out]	str	The memory area.
 * @param[in]	c	The byte to fill the memory area with.
 * @param[in]	n	Amount of bytes set to @p c.
 *
 * @returns	The pointer to the memory area @p str.
 */
void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*strp;

	strp = (unsigned char *)str;
	while (n-- > 0)
		*strp++ = (unsigned char)c;
	return (str);
}
