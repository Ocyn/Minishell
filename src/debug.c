/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/29 01:55:17 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_tabstr_display(char **tab)
{
	int	i;

	i = -1;
	printf("{");
	while (tab && tab[++i])
		printf("[%s] ", tab[i]);
	printf("}");
}

void	db_debug(t_linux *sys_l)
{
	t_cmd	*command;
	char	*line;

	line = NULL;
	command = sys_l->head;
	while (ft_strcmp(command->command.raw, "exit"))
	{
		line = readline("DB_DEBUG>> ");
		command = cmd_add_unit(command);
		command->command.raw = ft_strdup(line);
		str_edit(&command->command.raw, " ", "");
		printf("Saved to cell %d: {%s}\n", command->id, command->command.raw);
		s_free(&line);
	}
	s_free(&command->command.raw);
	cmd_display_list(sys_l->head);
	cmd_free_list(sys_l->head);
	fflush(stdout);
	return ;
}
