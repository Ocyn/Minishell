/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:50:03 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/21 17:16:24 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*lst_to_char(t_lst *lst)
{
	int		len;
	char	*new;
	t_lst	*buf;

	buf = lst;
	len = 0;
	while (buf)
	{
		if (buf->data != NULL && (ft_strcmp(buf->data, "$") == 0 \
		|| ft_strcmp(buf->data, "$?") == 0 || buf->data[0] != '$'))
			len += ft_strlen(buf->data);
		buf = buf->next;
	}
	new = s_malloc(sizeof(char) * len + 1);
	buf = lst;
	while (buf)
	{
		if (buf->data != NULL && (ft_strcmp(buf->data, "$") == 0 \
		|| ft_strcmp(buf->data, "$?") == 0 || buf->data[0] != '$'))
			ft_strcat(new, buf->data);
		buf = buf->next;
	}
	return (new);
}

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
