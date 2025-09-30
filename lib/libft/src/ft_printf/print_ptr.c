/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:21:00 by elie              #+#    #+#             */
/*   Updated: 2025/09/18 11:22:35 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_ptr(void *ptr)
{
	if (!ptr)
		return (print_str("(nil)"));
	print_str("0x");
	return (2 + print_hex((unsigned long long int)ptr));
}
