/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:57:34 by elie              #+#    #+#             */
/*   Updated: 2025/10/07 16:17:44 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_repoint(char **old_str, char *new_str)
{
	if (!old_str)
		return ;
	if (*old_str)
		free(*old_str);
	*old_str = new_str;
}
