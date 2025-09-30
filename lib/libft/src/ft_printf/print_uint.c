/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:21:08 by elie              #+#    #+#             */
/*   Updated: 2025/09/18 11:21:48 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_uint(unsigned int n)
{
	int	printed;

	printed = 0;
	if (n >= 10)
		printed += print_uint(n / 10);
	return (printed + print_char(('0' + (n % 10))));
}
