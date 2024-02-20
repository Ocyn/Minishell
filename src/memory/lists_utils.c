/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/20 11:28:38 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_lst	*lst_go_to(t_lst *list, int firstorlast)
{
	if (list && firstorlast)
	{
		while (firstorlast == -1 && list->prev)
			list = list->prev;
		while (firstorlast == 1 && list->next)
			list = list->next;
	}
	return (list);
}

int	lst_len(t_lst *list, int fromhere)
{
	t_lst	*len;
	int		i;

	i = -1;
	len = list;
	if (!fromhere)
		len = lst_go_to(list, -1);
	if (!len || !len->next)
		return (0);
	while (++i >= 0 && len)
		len = len->next;
	return (i);
}

t_lst	*lst_tab_to_list(char **tab)
{
	t_lst	*list;

	list = lst_init();
	while (tab && tab[0] && tab[0][0])
	{
		list = lst_add(list);
		list->data = ft_strdup(tab[0]);
		tab++;
	}
	list = lst_go_to(list, -1);
	return (list);
}

char	**lst_list_to_tab(t_lst *list)
{
	char	**tab;
	int		id;

	id = 0;
	tab = NULL;
	tab = s_malloc(sizeof(char *) * lst_len(list, 0));
	if (!tab || !list)
		return (NULL);
	while (list->next)
	{
		list = list->next;
		if (list->data)
		{
			tab[id] = ft_strdup(((char *)list->data));
			if (!tab[id])
				return (free_tab(tab, id), NULL);
		}
		else
			tab[id] = s_malloc(sizeof(char));
		id++;
	}
	return (tab);
}

int	find_str_in_list(t_lst *list_input, char *key)
{
	t_lst	*list;

	list = list_input;
	if (!list || !key)
		return (-1);
	while (list)
	{
		if (find_str_in_str((char *)list->data, key) != -1)
			return (list->id);
		list = list->next;
	}
	return (-1);
}
