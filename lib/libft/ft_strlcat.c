/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:07:52 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/06 19:29:29 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t c)
{
	size_t		kur;
	size_t		dlen;

	kur = 0;
	dlen = ft_strlen((char *)dest);
	if (dlen > c)
		return (ft_strlen((char *)src) + c);
	if (c == 0)
		return (ft_strlen((char *)src));
	while (src[kur] && (kur + dlen) < (c - 1))
	{
		dest[kur + dlen] = src[kur];
		kur++;
	}
	dest[kur + dlen] = '\0';
	return (dlen + ft_strlen((char *)src));
}
