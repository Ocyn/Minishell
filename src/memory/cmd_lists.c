/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/20 22:56:18 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
	if (cmd->meta.raw)
		free_tab(cmd->meta.raw, tablen(cmd->meta.raw));
	s_free(&cmd->meta.sraw);
	if (cmd->meta.exec_cmd)
		free_tab(cmd->meta.exec_cmd, tablen(cmd->meta.exec_cmd));
	if (cmd->meta.infile > 2)
		s_close(cmd->meta.infile);
	if (cmd->meta.outfile > 2)
		s_close(cmd->meta.outfile);
	if (tprev)
		tprev->next = cmd->next;
	if (tnext)
		tnext->prev = cmd->prev;
	free(cmd);
	cmd = NULL;
}

void	*cmd_free_list(t_cmd *cmd)
{
	if (cmd->id == 0)
		cmd = cmd->next;
	while (cmd)
	{
		free_tab(cmd->meta.raw, tablen(cmd->meta.raw));
		s_free(&cmd->meta.sraw);
		if (cmd->meta.exec_cmd)
			free_tab(cmd->meta.exec_cmd, tablen(cmd->meta.exec_cmd));
		if (cmd->meta.infile > 2)
			s_close(cmd->meta.infile);
		if (cmd->meta.outfile > 2)
			s_close(cmd->meta.outfile);
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
