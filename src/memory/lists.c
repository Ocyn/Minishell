/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/22 13:00:29 by aammirat         ###   ########.fr       */
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

t_lst	*lst_add_fragment_str(t_lst *last, char *str, int i, int j)
{
	int	index;

	index = 0;
	if (j - i == 0)
		return (last);
	last->data = s_malloc(sizeof(char) * (j - i + 1));
	if (!last->data)
	{
		last->data = NULL;
		return (last);
	}
	while (str[index + i] && index + i < j)
	{
		last->data[index] = str[index + i];
		index++;
	}
	last = lst_add(last);
	if (!last)
		return (NULL);
	return (last);
}

t_lst	*lst_rm(t_lst *list)
{
	t_lst	*tprev;
	t_lst	*tnext;

	tprev = NULL;
	tnext = NULL;
	if (!list)
		return (list);
	if (list->prev)
		tprev = list->prev;
	if (list->next)
		tnext = list->next;
	s_free(&list->data);
	if (tprev && tprev->next)
		tprev->next = list->next;
	if (tnext && tnext->prev)
		tnext->prev = list->prev;
	free(list);
	list = NULL;
	if (tprev->next)
		list = tprev->next;
	return (list);
}

void	*lst_free_list(t_lst *lst)
{
	if (lst && lst->prev)
		lst = lst_go_to(lst, -1);
	while (lst)
	{
		s_free(&lst->data);
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
