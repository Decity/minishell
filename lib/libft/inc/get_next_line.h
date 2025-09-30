/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:09:33 by ebelle            #+#    #+#             */
/*   Updated: 2025/05/13 12:09:34 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*read_to_buffer(int fd, char *buffer);
char	*get_line_from_buffer(char *buffer);
char	*trim_buffer(char *buffer);
size_t	gnl_strlen(char *str);
void	*gnl_calloc(size_t n);
void	gnl_free_and_null(char **ptr);
char	*gnl_strjoin(char *old_buffer, char *tmp);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strndup(char *s, size_t n);
#endif
