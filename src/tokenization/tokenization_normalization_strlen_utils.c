/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_normalization_strlen_utils.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:11:19 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/12 16:13:10 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenization_in_quote_heredoc(const char *str, int8_t curr_type,
	int8_t next_type)
{
	if (curr_type == TYPE_ARG && (next_type == TYPE_REDIRECTION_HEREDOC
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_REDIRECTION_HEREDOC
			|| get_redirection_type(str))
		&& next_type == TYPE_ARG)
		return (1);
	else if (curr_type == TYPE_REDIRECTION_HEREDOC
		&& str[0] && get_redirection_type(str + 1))
		return (1);
	else if ((curr_type == TYPE_SQUOTE || curr_type == TYPE_DQUOTE)
		&& (next_type == TYPE_REDIRECTION_HEREDOC
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_REDIRECTION_HEREDOC
			|| get_redirection_type(str))
		&& (next_type == TYPE_SQUOTE || next_type == TYPE_DQUOTE))
		return (1);
	return (0);
}

int	tokenization_in_quote_append(const char *str, int8_t curr_type,
	int8_t next_type)
{
	if (curr_type == TYPE_ARG && (next_type == TYPE_REDIRECTION_APPEND
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_REDIRECTION_APPEND || get_redirection_type(str))
		&& next_type == TYPE_ARG)
		return (1);
	else if (curr_type == TYPE_REDIRECTION_APPEND && str[0]
		&& get_redirection_type(str + 1))
		return (1);
	else if ((curr_type == TYPE_SQUOTE || curr_type == TYPE_DQUOTE)
		&& (next_type == TYPE_REDIRECTION_APPEND
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_REDIRECTION_APPEND || get_redirection_type(str))
		&& (next_type == TYPE_SQUOTE || next_type == TYPE_DQUOTE))
		return (1);
	return (0);
}

int	tokenization_in_quote_redirect_out(const char *str, int8_t curr_type,
	int8_t next_type)
{
	if (curr_type == TYPE_ARG && (next_type == TYPE_REDIRECTION_OUT
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_REDIRECTION_OUT || get_redirection_type(str))
		&& next_type == TYPE_ARG)
		return (1);
	else if (curr_type == TYPE_REDIRECTION_OUT && str[0]
		&& get_redirection_type(str + 1))
		return (1);
	else if ((curr_type == TYPE_SQUOTE || curr_type == TYPE_DQUOTE)
		&& (next_type == TYPE_REDIRECTION_OUT
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_REDIRECTION_OUT || get_redirection_type(str))
		&& (next_type == TYPE_SQUOTE || next_type == TYPE_DQUOTE))
		return (1);
	return (0);
}

int	tokenization_in_quote_redirect_in(const char *str, int8_t curr_type,
	int8_t next_type)
{
	if (curr_type == TYPE_ARG && (next_type == TYPE_REDIRECTION_IN
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_REDIRECTION_IN || get_redirection_type(str))
		&& next_type == TYPE_ARG)
		return (1);
	else if (curr_type == TYPE_REDIRECTION_IN && str[0]
		&& get_redirection_type(str + 1))
		return (1);
	else if ((curr_type == TYPE_SQUOTE || curr_type == TYPE_DQUOTE)
		&& (next_type == TYPE_REDIRECTION_IN
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_REDIRECTION_IN || get_redirection_type(str))
		&& (next_type == TYPE_SQUOTE || next_type == TYPE_DQUOTE))
		return (1);
	return (0);
}

int	tokenization_in_quote_pipe(const char *str, int8_t curr_type,
	int8_t next_type)
{
	if (curr_type == TYPE_ARG && (next_type == TYPE_PIPE
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_PIPE || get_redirection_type(str))
		&& next_type == TYPE_ARG)
		return (1);
	else if (curr_type == TYPE_PIPE && str[0] && get_redirection_type(str + 1))
		return (1);
	else if ((curr_type == TYPE_SQUOTE || curr_type == TYPE_DQUOTE)
		&& (next_type == TYPE_PIPE
			|| (str[0] && get_redirection_type(str + 1))))
		return (1);
	else if ((curr_type == TYPE_PIPE || get_redirection_type(str))
		&& (next_type == TYPE_SQUOTE || next_type == TYPE_DQUOTE))
		return (1);
	return (0);
}
