/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:13:24 by jcuzin            #+#    #+#             */
/*   Updated: 2023/09/10 22:08:26 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_print_result(const char *str, size_t index)
{
	long	result;

	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10;
		result = result + str[index++] - 48;
	}
	return (result);
}

long	ft_atoi(const char *str)
{
	size_t	index;
	int		sign;
	int		symb_count;

	index = 0;
	sign = 1;
	symb_count = 0;
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == ' ')
		index++;
	while (str[index] == '-' || str[index] == '+')
	{
		if (symb_count > 1)
			return (0);
		if (str[index] == '-' || str[index] == '+')
		{
			if (str[index] == '-')
				sign *= -1;
			symb_count++;
			index++;
		}
	}
	if (symb_count > 1)
		return (0);
	return (ft_print_result(str, index) * sign);
}
