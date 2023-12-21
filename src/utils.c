/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:24 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/21 13:56:39 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*put_in(char *str)
{
	int		i;
	int		size;
	char	*src;

	i = 0;
	size = ft_strlen(str);
	src = malloc(sizeof(char) * size + 1);
	if (!src)
		return (NULL);
	while (str[i])
	{
		src[i] = str[i];
		i++;
	}
	src[i] = '\0';
	return (src);
}

int	ft_memcmp(char *str, char *des)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (!des[i] || des[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (start >= (unsigned int)ft_strlen(s) || len == 0)
		return (NULL);
	if (len < ft_strlen(s) - start)
		str = malloc(len * sizeof(char) + 1);
	else
		str = malloc(ft_strlen(s) - start * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (i < len && s[i + start])
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
