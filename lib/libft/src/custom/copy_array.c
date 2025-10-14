/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:10:22 by elie              #+#    #+#             */
/*   Updated: 2025/10/14 13:45:55 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**copy_array(char **array)
{
	size_t	len;
	size_t	i;
	char	**copy;

	if (array == NULL)
		return (NULL);
	len = 0;
	while (array[len])
		len++;
	copy = ft_calloc((len + 1), sizeof(char *));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
		{
			free_array(&copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

char	**copy_narray(char **array, size_t n)
{
	size_t	i;
	char	**copy;

	if (array == NULL)
		return (NULL);
	copy = ft_calloc((n + 1), sizeof(char *));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < n && array[i])
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
		{
			free_array(&copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}


