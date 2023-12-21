/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:50:03 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/21 14:46:58 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

void	s_free(void **ptr_memory)
{
	if (ptr_memory && *ptr_memory)
	{
		free(ptr_memory);
		*ptr_memory = NULL;
	}
}

void	*s_malloc(size_t size)
{
	void	**array;

	*array = NULL;
	(void)array;
	if (!size)
		return (NULL);
	*array = malloc(sizeof(*array) * (size + 1));
	if (!*array)
		return (NULL);
	while (--size >= 0)
		array[size] = 0;
	return (*array);
}
