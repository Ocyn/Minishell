/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/18 06:49:02 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_lst	*lst_init(void)
{
	t_lst	*lst;

	lst = NULL;
	lst = s_malloc(sizeof(t_lst));
	if (!lst)
		return (NULL);
	lst->data = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	lst->id = 0;
	return (lst);
}

int	lst_len(t_lst list)
{
	t_lst	*len;
	int		i;

	i = -1;
	len = &list;
	if (!len || !len->next)
		return (0);
	while (++i >= 0 && len)
		len = len->next;
	return (i);
}

t_lst	*lst_add(t_lst *last)
{
	t_lst	*temp_prev;

	temp_prev = NULL;
	temp_prev = last;
	last->next = lst_init();
	if (!last->next)
		return (NULL);
	last = last->next;
	last->next = NULL;
	last->prev = temp_prev;
	last->id = temp_prev->id + 1;
	return (last);
}

void	lst_rm(t_lst *list)
{
	t_lst	*tprev;
	t_lst	*tnext;

	tprev = list->prev;
	tnext = list->next;
	if (list)
		s_free((char **)(&list->data));
	if (tprev)
		tprev->next = list->next;
	if (tnext)
		tnext->prev = list->prev;
	free(list);
	list = NULL;
}

void	*lst_free_list(t_lst *lst, int keep_head)
{
	if (lst->id == 0 && keep_head)
		lst = lst->next;
	while (lst)
	{
		s_free((char **)(&lst->data));
		if (lst->next)
		{
			lst = lst->next;
			free(lst->prev);
			lst->prev = NULL;
		}
		else
			break ;
	}
	free(lst);
	lst = NULL;
	return (NULL);
}
