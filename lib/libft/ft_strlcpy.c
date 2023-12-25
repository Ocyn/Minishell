/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:54:01 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/06 19:29:31 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	unsigned int	cursor;

	cursor = 0;
	if (size > 0)
	{
		while (src[cursor] != '\0' && cursor + 1 < size)
		{
			dest[cursor] = src[cursor];
			cursor++;
		}
		dest[cursor] = '\0';
	}
	return (ft_strlen(src));
}
