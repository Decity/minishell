/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:27:22 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 22:36:32 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Find the first matching instance of @p `character` in @p `ptr`.
 *
 * @param[in]	ptr			Memory area to read.
 * @param[in]	character	Instance to find.
 * @param[in]	size		Characters to read in bytes.
 *
 * @returns	Pointer to the matching byte, or NULL if it does not occur.
 */
void	*ft_memchr(const void *ptr, int character, size_t size)
{
	unsigned char	*strp;

	strp = (unsigned char *)ptr;
	while (size-- > 0)
	{
		if (*strp == (unsigned char)character)
			return (strp);
		strp++;
	}
	return (NULL);
}

/**
 * @brief Compare the first @p `num` bytes between @p `ptr1` and @p `ptr2`.
 *
 * @param[in]	ptr1	Pointer to the first memory area.
 * @param[in]	ptr2	Pointer to the second memory area.
 * @param[in]	num		Amount of bytes to compare.
 *
 * @retval 0 if @p `ptr1` and @p `ptr2` are equal.
 * @retval A negative value if @p `ptr1` is less than @p `ptr2`.
 * @retval A positive value if @p `ptr1` is greater than @p `ptr2`.
 */
int32_t	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t	i = 0;

	if (num == 0)
	{
		return (0);
	}
	while (((const uint8_t *)ptr1)[i] == ((const uint8_t *)ptr2)[i] && --num > 0)
	{
		i++;
	}
	return (((uint8_t *)ptr1)[i] - ((uint8_t *)ptr2)[i]);
}


/**
 * @brief Copy @p `num` bytes pointed from @p `src` to @p `dest`.
 *
 * @param[out]	dest	Pointer to the destination memory area.
 * @param[in]	src		Pointer to the source memory area.
 * @param[in]	num		Amount of bytes to copy from @p `src`.
 *
 * @return Pointer to @p `dest`.
 *
 * @note Behaviour is undefined if the copying happens between memory areas
 * @note that overlap.
 * @note Use ft_memmove if this is not intended.
 */
void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		((uint8_t *)dest)[i] = ((const uint8_t *)src)[i];
		i++;
	}
	return (dest);
}

/**
 * @brief Copy @p `num` bytes pointed from @p `src` to @p `dest`.
 *
 * @param[out]	dest	Pointer to the destination memory area.
 * @param[in]	src		Pointer to the source memory area.
 * @param[in]	num		Amount of bytes to copy from @p `src`.
 *
 * @return Pointer to @p dest.
 */
void	*ft_memmove(void *dest, const void *src, size_t num)
{
	while (num > 0)
	{
		((uint8_t *)dest)[num] = ((const uint8_t *)src)[num];
		num--;
	}
	return (dest);
}

/**
 * @brief Write @p `num` bytes of @p `character` pointed to by @p `ptr`.
 *
 * @param[out]	ptr			Pointed area to fill.
 * @param[in]	character	Character to fill @p `ptr` with.
 * @param[in]	num			Amount of @p `character` to write.
 *
 * @return Pointer to the ptr filled with @p `character` characters.
 */
void	*ft_memset(void *ptr, int32_t character, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		((uint8_t *)ptr)[i] = character;
	}
	return (ptr);
}
