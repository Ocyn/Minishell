/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:17:06 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/07 20:17:08 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	index_str;
	size_t	index_new_str;

	index_new_str = 0;
	if (start > (size_t)ft_strlen((char *)s))
		start = (size_t)ft_strlen((char *)s);
	if (len > (size_t)ft_strlen((char *)s))
		len = (size_t)ft_strlen((char *)s);
	index_str = start;
	while (s[index_str] && (len - index_new_str) > 0)
	{
		index_str++;
		index_new_str++;
	}
	new = malloc(sizeof(char) * (index_new_str + 1));
	if (new == NULL)
		return (NULL);
	index_str = start;
	index_new_str = 0;
	while (s[index_str] && len-- > 0)
		new[index_new_str++] = s[index_str++];
	new[index_new_str] = '\0';
	return (new);
}
