/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:50:03 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 01:56:46 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	*s_malloc(unsigned long size);
void	s_free(void **ptr_memory);
void	free_all(t_linux *shell);

void	s_free(void **ptr_memory)
{
	if (ptr_memory)
	{
		free(ptr_memory);
		ptr_memory = NULL;
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

void	free_tab(void **ptr_tab, size_t i)
{
	while (ptr_tab && i != 0)
	{
		s_free((void *)ptr_tab[i]);
		i--;
	}
	s_free((void *)ptr_tab);
}
