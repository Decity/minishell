/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:49:42 by elie              #+#    #+#             */
/*   Updated: 2025/10/22 17:12:22 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets the token type as num
 *
 * @return Token type as num, or 0 on empty str
 */
uint8_t	get_token_type(const char *str)
{
	if (!str || !str[0])
		return (0);
	if (!ft_strncmp(str, ">>", 2))
		return (TYPE_REDIRECTION_APPEND);
	if (!ft_strncmp(str, "<<", 2))
		return (TYPE_REDIRECTION_HEREDOC);
	if (!ft_strncmp(str, ">", 1))
		return (TYPE_REDIRECTION_OUT);
	if (!ft_strncmp(str, "<", 1))
		return (TYPE_REDIRECTION_IN);
	if (!ft_strncmp(str, "|", 1))
		return (TYPE_PIPE);
	if (!ft_strncmp(str, "\'", 1))
		return (TYPE_SQUOTE);
	if (!ft_strncmp(str, "\"", 1))
		return (TYPE_DQUOTE);
	if (ft_isspace(str[0]))
		return (TYPE_SPACE);
	return (TYPE_ARG);
}

/**
 * @return If redirection, returns redirection type as num. Else returns 0
 */
uint8_t	get_redirection_type(const char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (TYPE_REDIRECTION_APPEND);
	if (!ft_strncmp(str, "<<", 2))
		return (TYPE_REDIRECTION_HEREDOC);
	if (!ft_strncmp(str, ">", 1))
		return (TYPE_REDIRECTION_OUT);
	if (!ft_strncmp(str, "<", 1))
		return (TYPE_REDIRECTION_IN);
	return (0);
}

/**
 * @return If quote, returns quote type as num. Else returns 0
 */
uint8_t	get_quote_type(const char *str)
{
	if (!ft_strncmp(str, "\'", 1))
		return (TYPE_SQUOTE);
	if (!ft_strncmp(str, "\"", 1))
		return (TYPE_DQUOTE);
	return (0);
}

char	get_quote(const char c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return (0);
}
