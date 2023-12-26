/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/26 17:18:59 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_debug(t_linux *sys_l, void *memm1, void **memm2);

void	db_debug(t_linux *sys_l, void *memm1, void **memm2)
{
	t_cmd	*command;
	char	*line;

	(void)sys_l;
	(void)memm1;
	(void)memm2;
	command = NULL;
	sys_l->head = command;
	while (ft_strcmp(command->command.raw, "stop"))
	{
		line = readline("DB_DEBUG>> ");
		command = cmd_add_unit(command);
		command->command.raw = ft_strdup(line);
		printf("Saved to cell %d: {%s}\n", command->id, command->command.raw);
		s_free(&line);
	}
	cmd_display_list(sys_l->head);
	cmd_free_list(sys_l->head);
	fflush(stdout);
	return ;
}
