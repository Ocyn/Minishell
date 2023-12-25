/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:55:27 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/06 19:48:48 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str0, int c, size_t n)
{
	int				cursor;
	char			*str;
	char			chr;

	cursor = 0;
	str = (char *)str0;
	chr = (unsigned char) c;
	while (n > 0)
	{
		if (((int)str[cursor] == (c % 256)) || str[cursor] == chr)
			return (((void *) str) + cursor);
		cursor++;
		n--;
	}
	return (NULL);
}
