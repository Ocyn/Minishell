/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/29 23:50:23 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	cmd_init(t_cmd *cmd, char **data, int location)
{
	cmd->command.raw = NULL;
	cmd->command.one = NULL;
	cmd->command.full = NULL;
	cmd->type = 0;
	cmd->id = 0;
	if (!location || !data)
		return ;
	if (location == 1)
		cmd->command.raw = *data;
	if (location == 2)
		cmd->command.full = data;
	if (location == 3)
		cmd->command.env_var = data;
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
	cmd_init(last, NULL, 0);
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
	s_free(&cmd->command.one);
	if (cmd->command.full)
		free_tab(cmd->command.full, tablen(cmd->command.full));
	if (tprev)
		tprev->next = cmd->next;
	if (tnext)
		tnext->prev = cmd->prev;
	free(cmd);
}

void	*cmd_free_list(t_cmd *cmd)
{
	if (cmd->id == 0 && cmd->next)
	{
		printf("Skipping Cell %d [%p]: HEAD\n\n", cmd->id, cmd);
		cmd = cmd->next;
	}
	while (cmd)
	{
		printf("Free Cell %d [%p]\n", cmd->id, cmd);
		s_free(&cmd->command.raw);
		s_free(&cmd->command.one);
		if (cmd->command.full)
			free_tab(cmd->command.full, tablen(cmd->command.full));
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
	return (NULL);
}
