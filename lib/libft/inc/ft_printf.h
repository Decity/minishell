/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:20:19 by elie              #+#    #+#             */
/*   Updated: 2025/09/18 11:20:20 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		parse(int c, va_list args);
int		print_str(char *s);
int		print_char(int c);
int		print_ptr(void *ptr);
int		print_int(int n);
int		print_uint(unsigned int n);
int		print_hex(unsigned long long int n);
int		print_uhex(unsigned long long int n);

#endif