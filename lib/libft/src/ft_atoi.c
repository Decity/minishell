/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:52:08 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/06 16:46:56 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Convert a string to an integer.
 *
 * @param[in]	str	String to be converted.
 *
 * @returns		Converted integer value or 0 if conversion fails.
 *
 * @note	No error handling. Returns 0 for both the error aswell as the string.
 */
int	ft_atoi(const char *str)
{
	int	index;
	int	number;
	int	sign;

	index = 0;
	number = 0;
	sign = 1;
	while ((str[index] >= '\t' && str[index] <= '\r') || str[index] == ' ')
	{
		index++;
	}
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index++] == '-')
		{
			sign *= -1;
		}
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		number = number * 10 + (str[index++] - '0');
	}
	return (number * sign);
}
