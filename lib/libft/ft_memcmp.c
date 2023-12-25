/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:06:57 by jcuzin            #+#    #+#             */
/*   Updated: 2022/11/29 17:04:10 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			cursor;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	cursor = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (cursor < n)
	{
		if (ptr1[cursor] == ptr2[cursor] && cursor < n)
			cursor++;
		else
			return (ptr1[cursor] - ptr2[cursor]);
	}
	return (0);
}
