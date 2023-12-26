/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/25 23:16:32 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	cmd_init(t_cmd *cmd, t_cmd *nxt, t_cmd *prv)
{
	cmd->command = NULL;
	cmd->full_command = NULL;
	cmd->path = NULL;
	cmd->arg_n = 0;
	cmd->type = 0;
	cmd->id = 0;
	cmd->next = nxt;
	cmd->prev = prv;
}

t_cmd	*cmd_add_unit(t_cmd *cmd)
{
    t_cmd *prv;
    t_cmd *new_cmd;

    prv = cmd;
    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return (NULL);
    cmd->next = new_cmd;
    cmd_init(new_cmd, NULL, prv);
	new_cmd->id = prv->id + 1;
    return (new_cmd);
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
		s_free(cmd->command.pattern);
		s_free(cmd->command.one);
		s_free(cmd->command.path);
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
		printf("Cell %d:\tcommand [%s]\t|\tpath [%s]\t|\targ_n [%d]\t|\tnext [%p]\t|\tprev [%p]\n", list->id, list->command, list->path, list->arg_n, list->next, list->prev);
		list = list->next;
	}
}
