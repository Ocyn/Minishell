/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/06 19:25:25 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
