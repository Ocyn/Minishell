/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/29 02:25:08 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	cmd_init(t_cmd *cmd, char **data, int location)
{
	cmd->command.raw = NULL;
	cmd->command.path = NULL;
	cmd->command.one = NULL;
	cmd->command.full = NULL;
	cmd->command.env_var = NULL;
	cmd->command.arg_n = 0;
	cmd->type = 0;
	cmd->id = 0;
	if (!location || !data)
		return ;
	if (location == 1)
		cmd->command.raw = *data;
	if (location == 2)
		cmd->command.path = *data;
	if (location == 3)
		cmd->command.full = data;
	if (location == 4)
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
	s_free(&cmd->command.raw);
	s_free(&cmd->command.one);
	s_free(&cmd->command.path);
	if (cmd->command.full)
		free_tab(cmd->command.full, tablen(cmd->command.full));
	free(cmd);
	cmd = NULL;
}

void	*cmd_free_list(t_cmd *cmd)
{
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
	return (NULL);
}

void	cmd_display_list(t_cmd *list)
{
	while (list)
	{
		printf("Cell %d [%p]:\n", list->id, list);
		printf("\tType [%d]\n", list->type);
		printf("\tRaw [%s]\n", list->command.raw);
		printf("\tOne [%s]\n", list->command.one);
		printf("\tFull ");
		db_tabstr_display(list->command.full);
		printf("\n");
		printf("\targ_n [%d]\n", list->command.arg_n);
		printf("\tprev [%p]\n", list->prev);
		printf("\tnext [%p]\n\n", list->next);
		if (list->next)
			list = list->next;
		else
			break ;
	}
}
