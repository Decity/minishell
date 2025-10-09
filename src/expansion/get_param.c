/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:05:06 by elie              #+#    #+#             */
/*   Updated: 2025/10/09 10:38:17 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Gets the fully formatted variable name in a given @p `str`. Example: "$VAR" or "${VAR}"
 *
 * @param str a string that starts with '$'. 
 */
char	*get_parameter_var(const char *str)
{
	size_t	i;
	size_t	end;
	char	*result;

	if (!str || str[0] != '$')
		return (NULL);

	// Handle ${VAR} format
	if (str[1] == '{')
	{
		i = 2;
		while (str[i] && str[i] != '}')
			i++;
		if (str[i] != '}')
			return (NULL);
		end = i + 1;
	}
	// Handle $VAR format (alphanumeric + underscore)
	else
	{
		i = 1;
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (NULL);
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		end = i;
	}

	result = ft_calloc(end + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < end)
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}

/**
 * @brief Returns a str with the name of a formatted variable. i.e. ($USER or ${USER}) -> USER
 *
 * @param str A string that starts with '$'
 */
char	*get_parameter_name(const char *str)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*parameter_name;

	if (!str || str[0] != '$')
		return (NULL);

	// Handle ${VAR} format
	if (str[1] == '{')
	{
		i = 2;
		start = i;
		while (str[i] && str[i] != '}')
			i++;
		if (str[i] != '}')
			return (NULL);
		end = i;
	}
	// Handle $VAR format
	else
	{
		start = 1;
		i = start;
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (NULL);
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		end = i;
	}

	parameter_name = ft_calloc(end - start + 1, sizeof(char));
	if (!parameter_name)
		return (NULL);
	i = 0;
	while (start < end)
		parameter_name[i++] = str[start++];
	return (parameter_name);
}