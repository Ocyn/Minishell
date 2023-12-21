/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:50:03 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/21 22:15:05 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	*s_malloc(unsigned long size);
void	s_free(void **ptr_memory);
void	free_all(t_linux *shell);

void	s_free(void **ptr_memory)
{
	if (ptr_memory && *ptr_memory)
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
	while (0 < --size)
		byte_arr[size] = 0;
	return (byte_arr);
}

void	free_all(t_linux *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_history)
	{
		free(shell->history[i]);
		i++;
	}
	free(shell->history);
}
