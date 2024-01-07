/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 01:18:31 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	list_init(t_lst *lst)
{
	if (!lst)
		return ;
	lst->data = NULL;
	lst->id = 0;
	if (lst->prev)
		lst->id = lst->prev->id + 1;
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
	last->next = s_malloc(sizeof(t_lst));
	if (!last->next)
		return (NULL);
	last = last->next;
	last->next = NULL;
	last->prev = temp_prev;
	list_init(last);
	return (last);
}

void	lst_rm(t_lst *list)
{
	t_lst	*tprev;
	t_lst	*tnext;

	tprev = list->prev;
	tnext = list->next;
	if (list)
		s_free((char **)list->data);
	if (tprev)
		tprev->next = list->next;
	if (tnext)
		tnext->prev = list->prev;
	free(list);
	list = NULL;
}

void	*lst_free_list(t_lst *lst)
{
	printf("\nFree List:\n\n");
	if (lst->id == 0)
	{
		printf("\tSkipping Cell %d [%p]: HEAD\n\n", lst->id, lst);
		lst = lst->next;
	}
	while (lst)
	{
		printf("\tFree Cell %d [%p]: \n", lst->id, lst);
		printf("\t\tData: [%p]", lst->data);
		s_free((char **)lst->data);
		printf("\r\t  "__VALID_FREED"\n");
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
