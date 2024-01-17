/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocyn <ocyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:21:26 by ocyn              #+#    #+#             */
/*   Updated: 2024/01/17 16:05:06 by ocyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_redi	init_redi(void)
{
	t_redi	*template;

	template->fd = 0;
	template->fd = NULL;
}

void	init_struct(t_linux *shell)
{
	shell->head = s_malloc(sizeof(t_cmd));
	if (!shell->head)
		return ;
	cmd_init(shell->head);
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
