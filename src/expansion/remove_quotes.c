/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:11:34 by elie              #+#    #+#             */
/*   Updated: 2025/10/09 15:43:19 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// TODO: Should not remove quotes inside of quotes.
void	remove_quotation(char **str)
{
	char	*str_without_single_quotes;
	char	*str_without_either_quotes;

	str_without_single_quotes = ft_strreplace(*str, "\'", "");
	str_without_either_quotes = ft_strreplace(str_without_single_quotes, "\"", "");
	free_and_null(&str_without_single_quotes);
	ft_repoint(str, str_without_either_quotes);
}
