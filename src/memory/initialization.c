/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:21:26 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/30 21:22:46 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_redi	init_redi(void)
{
	t_redi	template;

	template.fd = 0;
	template.token = NULL;
	return (template);
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
