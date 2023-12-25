/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:19:46 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/07 13:49:34 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	int		i;
	size_t	i2;

	i = 0;
	i2 = 0;
	if (!find[i2] || find == NULL)
		return ((char *)str);
	while (str[i] != '\0' && (len - i) > 0)
	{
		while (str[i] == find[i2] && len - i > 0)
		{
			if (len && i2 + 1 >= ft_strlen((char *)find))
				return ((char *)str + i - i2);
			i++;
			i2++;
		}
		i -= i2;
		i2 = 0;
		i++;
	}
	return (NULL);
}
