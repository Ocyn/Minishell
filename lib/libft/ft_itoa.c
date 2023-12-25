/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:48:56 by jcuzin            #+#    #+#             */
/*   Updated: 2023/02/22 18:42:25 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

static int	len_of_str(int n)
{
	size_t	index;

	index = 0;
	if (n < 0)
	{
		n *= -1;
		index++;
	}
	while (n > 0)
	{
		n /= 10;
		index++;
	}
	return (index);
}

static char	*conv_to_char(int n, char *result, int sign)
{
	int	len;
	int	n_temp;

	len = len_of_str(n) - 1;
	if (n < 0)
		n *= -1;
	while (len >= 0)
	{
		n_temp = n;
		n_temp %= 10;
		result[len] = n_temp + 48;
		n /= 10;
		len--;
	}
	if (sign == 1)
		result[0] = '-';
	return (result);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*result;

	if (n == 0)
		return (ft_strdup((const char *)"0"));
	if (n == INT_MIN)
		return (ft_strdup((const char *)"-2147483648"));
	if (n < 0)
		sign = 1;
	else
		sign = 0;
	result = malloc(sizeof(char) * (len_of_str(n) + 1));
	if (result == NULL)
		return (NULL);
	result[len_of_str(n)] = '\0';
	result = conv_to_char(n, result, sign);
	return (result);
}
