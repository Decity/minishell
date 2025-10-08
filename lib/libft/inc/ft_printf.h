/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:59:02 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/08 19:08:47 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define DECIMAL "0123456789"
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"
# define S_INT32_MIN "-2147483648"
# define HEX_LENGTH 8
# define INT32_LENGTH 11
# define PTR_LENGTH 16
# define BASE_10 10
# define BASE_16 16

int32_t	ft_printf(const char *format, ...);
int32_t	ft_putnum(int32_t num);
int32_t	ft_putunum(uint32_t num);
int32_t	ft_putchar(int character);
int32_t	ft_putstr(const char *str);
int32_t	ft_puthex_upper(uint32_t num);
int32_t	ft_puthex_lower(uint32_t num);
int32_t	ft_putptr(uintptr_t num);

#endif