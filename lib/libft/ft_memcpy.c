/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:29:27 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/06 19:25:31 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest0, const void *src0, size_t n)
{
	char		*dest;
	const char	*src;
	int			cursor1;
	int			cursor2;

	if (!n || (!dest0 && !src0))
		return (dest0);
	dest = dest0;
	src = src0;
	cursor1 = 0;
	cursor2 = 0;
	while (n > 0)
	{
		dest[cursor1] = src[cursor2];
		cursor1++;
		cursor2++;
		n--;
	}
	return (dest);
}
