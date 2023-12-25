/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:16:56 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/07 20:17:01 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_if_occur(char const *s1, char const *set, int cursor)
{
	int	index;

	index = 0;
	while (set[index])
	{
		if (s1[cursor] == set[index])
			return (1);
		else
			index++;
	}
	return (0);
}

static int	sizeof_trim(char const *s1, char const *set)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (check_if_occur(s1, set, c) == 1)
	{
		c++;
		i++;
	}
	c = ft_strlen((char *)s1) - 1;
	while (check_if_occur(s1, set, c) == 1)
	{
		c--;
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		cursor;
	size_t		cursor2;
	char		*result1;
	int			trim;

	if (s1[0] == '\0')
		return (ft_strdup(s1));
	cursor = 0;
	cursor2 = 0;
	trim = sizeof_trim(s1, set);
	if (trim >= (int)ft_strlen((char *)s1))
		return (ft_strdup((const char *)"\0"));
	result1 = malloc(sizeof(char) * (ft_strlen((char *)s1) \
	- trim + 1));
	if (result1 == NULL)
		return (NULL);
	while (check_if_occur(s1, set, cursor) == 1)
		if (s1[cursor++ + 1] == '\0')
			return ("\0");
	while ((size_t)cursor2 < (ft_strlen((char *)s1) - trim))
		result1[cursor2++] = s1[cursor++];
	result1[cursor2] = '\0';
	return (result1);
}
