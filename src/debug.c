/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/25 21:28:37 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_debug(t_linux *sys_l, void *memm1, void **memm2);

void	db_debug(t_linux *sys_l, void *memm1, void **memm2)
{
	t_cmd	*commands;
	char	*line;

	(void)sys_l;
	(void)memm1;
	(void)memm2;
	commands = malloc(sizeof(t_cmd));
	cmd_init(commands, NULL, NULL);
	commands->command = ft_strdup("START");
	sys_l->cmd_h = commands;
	while (ft_strcmp(commands->command, "stop"))
	{
		line = readline("DB_DEBUG>> ");
		commands = cmd_add_unit(commands);
		commands->command = ft_strdup(line);
		printf("Saved to cell %d: {%s}\n", commands->id, commands->command);
		s_free(&line);
	}
	cmd_display_list(sys_l->cmd_h);
	cmd_free_list(sys_l->cmd_h);
	fflush(stdout);
	return ;
}
