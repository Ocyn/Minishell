/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/29 05:12:16 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_tabstr_display(char **tab)
{
	int	i;

	i = -1;
	printf("{");
	while (tab && tab[++i])
		printf(" [%s]", tab[i]);
	printf(" }");
}

void	db_display_list(t_cmd *list)
{
	printf("\nList Resume:\n");
	if (list->next)
	{
		printf("Cell %d [%p]: HEAD\n\n", list->id, list);
		list = list->next;
	}
	while (list)
	{
		printf("Cell %d [%p]:\n", list->id, list);
		printf("\tType\t[%d]\n", list->type);
		printf("\tRaw\t[%s]\n", list->command.raw);
		printf("\tOne\t[%s]\n", list->command.one);
		printf("\tFull\t");
		db_tabstr_display(list->command.full);
		printf("\n");
		printf("\tArg_n\t[%d]\n", list->command.arg_n);
		printf("\tInfile\t[%d]\n", list->infile);
		printf("\tOutfile\t[%d]\n", list->outfile);
		printf("\tPrev\t[%p]\n", list->prev);
		printf("\tNext\t[%p]\n\n", list->next);
		if (list->next)
			list = list->next;
		else
			break ;
	}
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
	db_display_list(sys_l->head);
	cmd_free_list(sys_l->head);
	fflush(stdout);
	return ;
}
