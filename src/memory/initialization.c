/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:21:26 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/18 08:54:55 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	change_oldpwd(t_linux *shell)
{
	if (shell->oldpwd)
		s_free(&shell->oldpwd);
	shell->oldpwd = getcwd(NULL, 0);
}

void	cmd_init(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->id = 0;
	cmd->meta.raw = NULL;
	cmd->meta.sraw = NULL;
	cmd->meta.exec_cmd = NULL;
	cmd->meta.infile = 0;
	cmd->meta.outfile = 0;
}

void	init_struct(t_linux *shell)
{
	shell->head = s_malloc(sizeof(t_cmd));
	if (!shell->head)
		return ;
	cmd_init(shell->head);
	g_sign = 0;
	shell->oldpwd = NULL;
	shell->prompt = NULL;
	shell->head->next = NULL;
	shell->head->prev = NULL;
	shell->head->id = 0;
	shell->envi = NULL;
	shell->end = 0;
	shell->count_cmd = 0;
	shell->token = NULL;
	shell->command = shell->head;
	change_oldpwd(shell);
}
