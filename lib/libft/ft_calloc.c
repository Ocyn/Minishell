/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:33:20 by jcuzin            #+#    #+#             */
/*   Updated: 2023/02/22 18:19:34 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned long	cursor;
	char			*str;

	cursor = 0;
	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	str = malloc(size * count);
	if (str == NULL)
		return (NULL);
	while (cursor < (size * count))
		str[cursor++] = 0;
	return ((void *)str);
}
