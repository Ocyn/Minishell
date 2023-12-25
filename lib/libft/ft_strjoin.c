/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:16:36 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/07 20:16:40 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		cursor1;
	int		cursor2;
	char	*result;

	cursor1 = 0;
	cursor2 = 0;
	result = malloc(sizeof(char) * (ft_strlen(&*(char *) s1) \
	+ ft_strlen(&*(char *) s2)) + 1);
	if (result == NULL)
		return (NULL);
	while (s1[cursor1])
	{
		result[cursor2] = s1[cursor1];
		cursor1++;
		cursor2++;
	}
	cursor1 = 0;
	while (s2[cursor1])
	{
		result[cursor2] = s2[cursor1];
		cursor1++;
		cursor2++;
	}
	result[cursor2] = '\0';
	return (result);
}
