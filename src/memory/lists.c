/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/19 04:31:18 by jcuzin           ###   ########.fr       */
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

t_lst	*lst_rm(t_lst *list)
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
	if (tprev->next)
		return (tprev->next);
	if (tnext->prev)
		return (tnext->prev);
	return (list);
}

void	*lst_free_list(t_lst *lst)
{
	if (lst && lst->prev)
		lst = lst_go_to(lst, -1);
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
