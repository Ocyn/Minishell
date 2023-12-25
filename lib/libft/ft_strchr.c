/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:58:40 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/06 19:53:28 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	cursor;

	cursor = 0;
	if (c > 256)
		c %= 256;
	if (c == 0)
		return ((&*(char *)str + ft_strlen((char *)str)));
	while (str[cursor])
	{
		if (str[cursor] == c)
			return (&*(char *)str + cursor);
		cursor++;
	}
	return (0);
}
