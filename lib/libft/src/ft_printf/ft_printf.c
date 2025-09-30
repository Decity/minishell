/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:20:08 by elie              #+#    #+#             */
/*   Updated: 2025/09/18 11:21:56 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse(int c, va_list args)
{
	if (c == '%')
		return (print_char('%'));
	if (c == 'c')
		return (print_char(va_arg(args, int)));
	if (c == 's')
		return (print_str(va_arg(args, char *)));
	if (c == 'p')
		return (print_ptr(va_arg(args, void *)));
	if (c == 'd' || c == 'i')
		return (print_int(va_arg(args, int)));
	if (c == 'u')
		return (print_uint(va_arg(args, unsigned int)));
	if (c == 'x')
		return (print_hex(va_arg(args, unsigned int)));
	if (c == 'X')
		return (print_uhex(va_arg(args, unsigned int)));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	size_t	i;
	size_t	n;
	va_list	args;

	va_start(args, s);
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == '\0')
				return (n);
			n += parse(s[i], args);
		}
		else
			n += write(1, &s[i], 1);
		i++;
	}
	va_end(args);
	return (n);
}

// #include <stdio.h>
// int main()
// {
// 	int ret1, ret2;

// 	// 1. Simple string
// 	ret1 = ft_printf("Hello, world!\n");
// 	ret2 = printf("Hello, world!\n");
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// 	// 2. Character
// 	ret1 = ft_printf("Char: %c\n", 'A');
// 	ret2 = printf("Char: %c\n", 'A');
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// 	// 3. String
// 	ret1 = ft_printf("String: %s\n", "Codam");
// 	ret2 = printf("String: %s\n", "Codam");
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

	// // 3.a
	// char *null_str = NULL
	// 	ret1 = ft_printf("String: %s\n", null_str);
	// 	ret2 = printf("String: %s\n", null_str);
	// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// 	// 4. Percent sign
// 	ret1 = ft_printf("Percent: %%\n");
// 	ret2 = printf("Percent: %%\n");
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// 	// 5. Integer
// 	ret1 = ft_printf("Integer: %d\n", 42);
// 	ret2 = printf("Integer: %d\n", 42);
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// 	// 6. Negative integer
// 	ret1 = ft_printf("Negative: %i\n", -42);
// 	ret2 = printf("Negative: %i\n", -42);
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// 	// 7. Unsigned integer
// 	ret1 = ft_printf("Unsigned: %u\n", 3000000000U);
// 	ret2 = printf("Unsigned: %u\n", 3000000000U);
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// 	// 8. Hexadecimal lowercase
// 	ret1 = ft_printf("Hex: %x\n", 16);
// 	ret2 = printf("Hex: %x\n", 16);
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// 	// 9. Hexadecimal uppercase
// 	ret1 = ft_printf("HEX: %X\n", 255);
// 	ret2 = printf("HEX: %X\n", 255);
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// 	// 10. ptr
// 	int x = 42;
// 	ret1 = ft_printf("ptr: %p\n", &x);
// 	ret2 = printf("ptr: %p\n", &x);
// 	printf("Return values: ft_printf=%d, printf=%d\n\n", ret1, ret2);

// FAULT INPUTS
// MORE MIXES
// EDGE CASES

// 	return 0;
// }