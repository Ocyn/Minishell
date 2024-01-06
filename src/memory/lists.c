/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/04 13:57:18 by jcuzin           ###   ########.fr       */
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

int	lst_len(t_lst *list)
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
	cmd_init(last);
	return (last);
}

void	cmd_rm(t_lst *list)
{
	t_lst	*tprev;
	t_lst	*tnext;

	tprev = list->prev;
	tnext = list->next;
	free_tab(list, tablen(list));
	if (list)
		free_tab(list, tablen(list));
	if (tprev)
		tprev->next = list->next;
	if (tnext)
		tnext->prev = list->prev;
	free(list);
	list = NULL;
}

void	*cmd_free_list(t_lst *cmd)
{
	printf("\nFree List:\n\n");
	if (cmd->id == 0)
	{
		printf("\tSkipping Cell %d [%p]: HEAD\n\n", cmd->id, cmd);
		cmd = cmd->next;
	}
	while (cmd)
	{
		printf("\tFree Cell %d [%p]: \n", cmd->id, cmd);
		printf("\t\tRaw: [%s]", cmd->command.raw);
		s_free(&cmd->command.raw);
		printf("\r\t  "__VALID_FREED"\n");
		db_tabstr_display(cmd->command.prefixes, "\t\tPrefixes", -1);
		free_tab(cmd->command.prefixes, tablen(cmd->command.prefixes));
		printf("\r\t  "__VALID_FREED"\n");
		db_tabstr_display(cmd->command.args, "\t\tArgs", -1);
		free_tab(cmd->command.args, tablen(cmd->command.args));
		printf("\r\t  "__VALID_FREED"\n");
		if (cmd->next)
		{
			cmd = cmd->next;
			free(cmd->prev);
			cmd->prev = NULL;
		}
		else
			break ;
	}
	free(cmd);
	cmd = NULL;
	return (NULL);
}
