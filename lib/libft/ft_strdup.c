/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:16:20 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/07 20:16:22 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		cursor;
	char	*str;

	cursor = 0;
	str = malloc((sizeof(char) * ft_strlen((char *)s1)) + 1);
	if (str == NULL)
		return (NULL);
	cursor = 0;
	while (s1[cursor])
	{
		str[cursor] = s1[cursor];
		cursor++;
	}
	str[cursor] = '\0';
	return (&*(char *) str);
}
