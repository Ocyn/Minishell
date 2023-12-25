/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:50:03 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 06:39:51 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	s_free(char **ptr_memory)
{
	if (*ptr_memory)
	{
		free(*ptr_memory);
		*ptr_memory = NULL;
	}
}

void	*s_malloc(unsigned long size)
{
	unsigned char	*byte_arr;
	void			*array;

	array = NULL;
	byte_arr = NULL;
	if (!size)
		return (NULL);
	array = malloc(size);
	if (!array)
		return (NULL);
	byte_arr = (unsigned char *)array;
	ft_bzero(byte_arr, size);
	return (byte_arr);
}

void	free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		s_free(&tab[i]);
		i--;
	}
	s_free((char **)&tab);
}
