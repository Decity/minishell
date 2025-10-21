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

# define TYPE_ARG 1
# define TYPE_SPACE 2
# define TYPE_SQUOTE 3
# define TYPE_DQUOTE 4
# define TYPE_PIPE 5
# define TYPE_REDIRECTION_IN 6
# define TYPE_REDIRECTION_OUT 7
# define TYPE_REDIRECTION_APPEND 8
# define TYPE_REDIRECTION_HEREDOC 9

#endif
