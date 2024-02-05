/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:52:02 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/02 13:10:28 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	cmd_init(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->command.raw = NULL;
	cmd->command.exec_cmd = NULL;
	cmd->command.env_var = NULL;
	cmd->infile = init_redi();
	cmd->outfile = init_redi();
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
	if (cmd->command.raw)
		free_tab(cmd->command.raw, tablen(cmd->command.raw));
	if (cmd->command.exec_cmd)
		free_tab(cmd->command.exec_cmd, tablen(cmd->command.exec_cmd));
	s_free(&cmd->infile.token);
	s_free(&cmd->outfile.token);
	close(cmd->outfile.fd);
	close(cmd->infile.fd);
	if (tprev)
		tprev->next = cmd->next;
	if (tnext)
		tnext->prev = cmd->prev;
	free(cmd);
	cmd = NULL;
}

void	*cmd_free_list(t_cmd *cmd)
{
	//db_print_custom_font("\nFree List\n\n", FE_UND);
	if (cmd->id == 0)
	{
		//printf("\t"FE_REV""FE_BOL"Cell %d"FRR" [%p]: HEAD\n\n", cmd->id, cmd);
		cmd = cmd->next;
	}
	while (cmd)
	{
		//printf("\t"FE_REV""FE_BOL"Cell %d"FRR" [%p]: \n", cmd->id, cmd);
		//printf("\r\t"__VALID_FREED"\n");
		//db_tabstr_display(cmd->command.raw, "\t\tRaw", -1);
		free_tab(cmd->command.raw, tablen(cmd->command.raw));
		//printf("\r\t"__VALID_FREED"\n");
		if (cmd->command.exec_cmd)
		{
			//db_tabstr_display(cmd->command.exec_cmd, "\t\texec_cmd", -1);
			free_tab(cmd->command.exec_cmd, tablen(cmd->command.exec_cmd));
			//printf("\r\t"__VALID_FREED"\n");
		}
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
