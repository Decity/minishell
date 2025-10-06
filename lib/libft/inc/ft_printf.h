/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:59:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 22:20:22 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# ifndef HEX_UPPER
#  define HEX_UPPER "0123456789ABCDEF"
# endif
# ifndef HEX_LOWER
#  define HEX_LOWER "0123456789abcdef"
# endif
# include "libft.h"
# include <stdarg.h> // va_

int	ft_printf(const char *format, ...);
int	ft_puthex(unsigned int hex, char specifier);
int	ft_putchar(int c);
int	ft_putnum(int num);
int	ft_putptr(uintptr_t ptr);
int	ft_putstr(char *str);
int	ft_putunum(unsigned int num);

#endif