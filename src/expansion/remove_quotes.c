/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:11:34 by elie              #+#    #+#             */
/*   Updated: 2025/11/25 11:21:31 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Remove outer quotes from a string
 */
void	remove_quotation(char **str)
{
	char	*result;
	char	*src;
	size_t	i;
	size_t	j;
	char	quote;

	if (!str || !*str)
		return;
	result = malloc(ft_strlen(*str) + 1);
	if (!result)
		return;
	src = *str;
	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (quote == 0 && (src[i] == '\'' || src[i] == '\"'))
		{
			quote = src[i];
			i++;
			continue;
		}
		else if (quote != 0 && src[i] == quote)
		{
			quote = 0;
			i++;
			continue;
		}
		result[j++] = src[i++];
	}
	result[j] = '\0';
	free(*str);
	*str = result;
}
