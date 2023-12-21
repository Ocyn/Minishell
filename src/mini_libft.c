/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:27:01 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/21 23:29:27 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ft_print_result(const char *str, size_t index)
{
	int	result;

	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10;
		result = result + str[index++] - 48;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	size_t	index;
	int		sign;
	int		symb_count;

	index = 0;
	sign = 1;
	symb_count = 0;
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == ' ')
		index++;
	while (str[index] == '-' || str[index] == '+')
	{
		if (symb_count > 1)
			return (0);
		if (str[index] == '-' || str[index] == '+')
		{
			if (str[index] == '-')
				sign *= -1;
			symb_count++;
			index++;
		}
	}
	if (symb_count > 1)
		return (0);
	return (ft_print_result(str, index) * sign);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			cursor;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	cursor = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (cursor < n)
	{
		if (ptr1[cursor] == ptr2[cursor] && cursor < n)
			cursor++;
		else
			return (ptr1[cursor] - ptr2[cursor]);
	}
	return (0);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst0;
	unsigned const char	*src0;

	if (!dst && !src)
		return (dst);
	dst0 = (unsigned char *)dst;
	src0 = (unsigned char *)src;
	if (src < dst)
		while (len--)
			dst0[len] = src0[len];
	else
		ft_memcpy(dst0, src0, len);
	return (dst);
}
void	*ft_memset(void *str, int c, size_t n)
{
	int		cursor;
	char	*nstr;

	cursor = 0;
	nstr = (char *) str;
	while (n > 0)
	{
		nstr[cursor] = c;
		cursor++;
		n--;
	}
	return (str);
}
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
	while (s1 && s1[cursor1])
		result[cursor2++] = s1[cursor1++];
	cursor1 = 0;
	while (s2 && s2[cursor1])
		result[cursor2++] = s2[cursor1++];
	result[cursor2] = '\0';
	free(s1);
	free(s2);
	return (result);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	cursor1;
	int	cursor2;

	cursor1 = 0;
	cursor2 = 0;
	while (((unsigned char)s1[cursor1] != '\0' \
	|| (unsigned char)s2[cursor2] != '\0') && n > 0)
	{
		if ((unsigned char)s1[cursor1] > (unsigned char)s2[cursor2])
			return (1);
		if ((unsigned char)s1[cursor1] < (unsigned char)s2[cursor2])
			return (-1);
		cursor1++;
		cursor2++;
		n--;
	}
	return (0);
}
