/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:00:22 by elie              #+#    #+#             */
/*   Updated: 2025/10/14 17:26:38 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# ifndef DEBUG
#  define DEBUG false
# endif

# define FAILURE 0
# define SUCCESS 1

# define REDIRECTION_IN 1
# define REDIRECTION_OUT 2
# define REDIRECTION_APPEND 3
# define REDIRECTION_HEREDOC 4

#endif
