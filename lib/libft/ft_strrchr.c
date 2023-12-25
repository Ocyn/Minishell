/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:08:14 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/06 19:57:56 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		cursor;
	char	*result;

	if (c > 256)
		c %= 256;
	cursor = ft_strlen((char *)str);
	result = (char *)str;
	while (cursor >= 0)
	{
		if (str[cursor] == c)
			return (result + cursor);
		cursor--;
	}
	return (NULL);
}
