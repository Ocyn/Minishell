/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:50:14 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/21 21:20:19 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
