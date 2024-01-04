/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/04 09:00:37 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	cmd_init(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->command.raw = NULL;
	cmd->command.prefixes = NULL;
	cmd->command.args = NULL;
	cmd->type = 0;
	cmd->id = 0;
}

int	list_len(t_cmd list)
{
	t_cmd	*len;
	int		i;

	i = -1;
	len = &list;
	if (!len || !len->next)
		return (0);
	while (++i >= 0 && len)
		len = len->next;
	return (i);
}

t_cmd	*cmd_add_unit(t_cmd *last)
{
	t_cmd	*temp_prev;

	temp_prev = NULL;
	temp_prev = last;
	last->next = malloc(sizeof(t_cmd));
	if (!last->next)
		return (NULL);
	last = last->next;
	last->next = NULL;
	last->prev = temp_prev;
	cmd_init(last);
	last->id = temp_prev->id + 1;
	return (last);
}

void	cmd_rm_unit(t_cmd *cmd)
{
	t_cmd	*tprev;
	t_cmd	*tnext;

	tprev = cmd->prev;
	tnext = cmd->next;
	s_free(&cmd->command.raw);
	free_tab(cmd->command.prefixes, tablen(cmd->command.prefixes));
	if (cmd->command.args)
		free_tab(cmd->command.args, tablen(cmd->command.args));
	if (tprev)
		tprev->next = cmd->next;
	if (tnext)
		tnext->prev = cmd->prev;
	free(cmd);
	cmd = NULL;
}

void	*cmd_free_list(t_cmd *cmd)
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
