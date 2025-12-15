/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_validation_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:41:23 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/08 17:42:07 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenize_consec(char *str, size_t consecutive,
	int8_t next)
{
	consecutive++;
	if (next == TYPE_PIPE)
		return (FAILURE);
	if (has_redirection_target(str) == false)
		return (FAILURE);
	if (get_redirection_type(str + 1) && *str != *(str + 1))
		return (FAILURE);
	if (consecutive == 3)
		return (FAILURE);
	return (SUCCESS);
}

static void	tokenization_update_quote(char *str, char *in_quote)
{
	if (*in_quote == 0 && get_quote(*str))
		*in_quote = *str;
	else if (*in_quote && *in_quote == *str)
		*in_quote = 0;
}

static bool	tokenization_pipe_check(char *str, char in_quote, int8_t curr,
	int8_t next)
{
	if (in_quote == 0 && curr == TYPE_PIPE
		&& (next == TYPE_PIPE || has_redirection_target(str) == false))
	{
		return (true);
	}
	return (false);
}

static bool	validate_token_check(char *str, size_t *count, char *in_quote,
	int8_t next)
{
	int8_t	curr;

	tokenization_update_tokens(str, &curr, &next);
	tokenization_update_quote(str, in_quote);
	if (!*in_quote && is_redirection(str))
	{
		if (tokenize_consec(str, *count, next) == FAILURE)
			return (FAILURE);
	}
	else if (tokenization_pipe_check(str, *in_quote, curr, next))
		return (FAILURE);
	else
		*count = 0;
	return (SUCCESS);
}

/**
 * @brief validates the syntax of redirections and pipes
 */
bool	validate_token_str(char *str)
{
	size_t	i;
	size_t	count_consecutive;
	int8_t	next;
	char	in_quote;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		return (FAILURE);
	i = 0;
	count_consecutive = 0;
	in_quote = 0;
	while (str[i])
	{
		next = 0;
		if (validate_token_check(str + i, &count_consecutive,
				&in_quote, next) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
