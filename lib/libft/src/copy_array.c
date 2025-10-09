/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:10:22 by elie              #+#    #+#             */
/*   Updated: 2025/10/09 14:13:11 by dbakker          ###   ########.fr       */
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
	copy = malloc(sizeof(char *) * (len + 1));
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
	copy[i] = NULL;
	return (copy);
}
