/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:09:57 by elie              #+#    #+#             */
/*   Updated: 2025/10/09 14:12:48 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_array(char ***array)
{
	size_t	i;

	if (array == NULL || *array == NULL)
	{
		return ;
	}
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

/**
 * @brief Free an array of pointers of @p `size` length.
 *
 * @param[out]	ptr		Pointer to the array.
 * @param[in]	size	Size of the array of pointers.
 */
void	ft_free2d(void **ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(ptr[i++]);
	}
	free(ptr);
}
