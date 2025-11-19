/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:09:04 by elie              #+#    #+#             */
/*   Updated: 2025/11/19 15:33:50 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This is optional, see source for more info
 * 	- Should not expand if inside ' '
 * 	- Should not expand if inside ""
 *
 * Source: https://www.gnu.org/software/bash/manual/html_node/Tilde-Expansion.html
 */
void	expand_tilde(char **str)
{
	const char	*temp_home = "/home/team_unicode_whitespace";

	char *new_str = ft_strreplace(*str, "~", temp_home);
	ft_repoint(str, new_str);
}