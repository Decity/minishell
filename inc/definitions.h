/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:00:22 by elie              #+#    #+#             */
/*   Updated: 2025/11/15 14:52:51 by dbakker          ###   ########.fr       */
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

# define HEREDOC_LIMIT 16

# ifndef HEREDOC_FILENAME_LENGTH
#  define HEREDOC_FILENAME_LENGTH 16
# endif

#endif
