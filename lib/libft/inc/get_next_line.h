/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:48:34 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:53:10 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif
# include "libft.h"
# include <stdint.h> // SIZE_MAX

char	*get_next_line(int fd);
#endif
