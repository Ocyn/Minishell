/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:50:03 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/07 04:09:54 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
	ft_memset(byte_arr, 0, size);
	return (byte_arr);
}

void	free_tab(char **tab, int i)
{
	if (!tab)
		return ;
	while (i >= 0)
	{
		s_free(&tab[i]);
		i--;
	}
	s_free((char **)&tab);
}

void	cut_and_paste(void **cut, void **paste, size_t sizeof_cut)
{
	if (!*cut)
		return ;
	if (paste && *paste)
	{
		free(*paste);
		*paste = NULL;
	}
	*paste = s_malloc(sizeof_cut);
	ft_memmove(*paste, *cut, sizeof_cut);
	free(*cut);
	*cut = NULL;
}

// char	**list_to_tab(t_cmd *list)
// {
// 	char	**tab;
// 	int		len;
// 	int		i;

// 	i = -1;
// 	len = list_len(*list);
// 	tab = NULL;
// 	if (!list || !list->next)
// 		return (NULL);
// 	if (list->id == 0)
// 		list = list->next;
// 	tab = s_malloc(sizeof(char *) * len);
// 	if (!tab)
// 		return (NULL);
// 	while (++i > -1 && list)
// 	{
// 		tab[i] = ft_strdup(list->command.sraw);
// 		list = list->next;
// 	}
// 	return (tab);
// }
