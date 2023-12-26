/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/26 17:14:22 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	cmd_init(t_cmd *cmd, char **data, int location)
{
	cmd->command.raw = NULL;
	cmd->command.path = NULL;
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
	last->next = malloc(sizeof(t_cmd));
	if (!last->next)
		return (NULL);
	last = last->next;
	last->next = NULL;
	cmd_init(last, NULL, 0);
	return (last);
}

void	*cmd_rm_unit(t_cmd *cmd, t_cmd *head, int last, int first)
{
	t_cmd	*prv;

	if (last && !first)
	{
		while (cmd->next)
		{
			prv = cmd;
			cmd = cmd->next;
		}
		free(cmd);
		cmd = NULL;
	}
	else if (!last && first)
	{
		prv = cmd->next;
		free(cmd);
		cmd = NULL;
		head = prv;
	}
	return (NULL);
}

void	*cmd_free_list(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd->next)
	{
		s_free(&cmd->command.raw);
		s_free(&cmd->command.one);
		s_free(&cmd->command.path);
		free_tab(cmd->command.full, cmd->command.arg_n);
		temp = cmd;
		cmd = cmd->next;
		free(temp);
		temp = NULL;
	}
	if (cmd)
	{
		free(cmd);
		cmd = NULL;
	}
	return (NULL);
}

void	cmd_display_list(t_cmd *list)
{
	while (list->next)
	{
		printf("Cell %d:\tRaw [%s] |Trimmed command [%s]\t|\tpath [%s]\t|\targ_n [%d]\t|\tnext [%p]\t|\tprev [%p]\n", list->id, list->command.raw, list->command.one, list->command.path, list->command.arg_n, list->next, list->prev);
		list = list->next;
	}
}
