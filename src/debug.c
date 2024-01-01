/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/01 11:31:10 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_tabstr_display(char **tab)
{
	int	i;

	i = -1;
	printf("[");
	while (tab && tab[++i])
		printf(" {%s}", tab[i]);
	printf(" ]");
}

void	db_display_list(t_cmd *list)
{
	printf("\nList Resume:\n\n");
	if (list->next)
	{
		printf("\tCell %d [%p]: HEAD\n\n", list->id, list);
		list = list->next;
	}
	while (list)
	{
		printf("\tCell %d [%p]:\n", list->id, list);
		if (list->type == SINGLE_CMD)
			printf("\t\tType\t[%d]_SINGLE_COMMAND\n", list->type);
		if (list->type == PIPE_CMD)
			printf("\t\tType\t[%d]_PIPE\n", list->type);
		if (list->type == DOLLARSIGN_CMD)
			printf("\t\tType\t[%d]_DOLLARSIGN\n", list->type);
		if (list->type == INFILE_CMD)
			printf("\t\tType\t[%d]_INFILE\n", list->type);
		if (list->type == OUTFILE_CMD)
			printf("\t\tType\t[%d]_OUTFILE\n", list->type);
		if (list->type == HEREDOC)
			printf("\t\tType\t[%d]_HEREDOC\n", list->type);
		if (list->type == OUTFILE_ADDER)
			printf("\t\tType\t[%d]_OUTFILE_ADDER\n", list->type);
		printf("\t\tRaw\t[%s]\n", list->command.raw);
		printf("\t\tOne\t[%s]\n", list->command.one);
		printf("\t\tFull\t");
		db_tabstr_display(list->command.full);
		printf("\n");
		printf("\t\tPrev\t[%p]\n", list->prev);
		printf("\t\tNext\t[%p]\n\n", list->next);
		if (list->next)
			list = list->next;
		else
			break ;
	}
}

void	db_debug(t_linux *sys_l)
{
	t_cmd	*command;
	char	*prompt;
	char	*line;

	line = NULL;
	prompt = NULL;
	command = sys_l->head;
	(void)line;
	prompt = prompt_tuning("[Minishell |", "#", "FC_PUR BN_GRA FE_BOL");
	printf("\n\nCustom Prompt: [%s]\n\n", prompt);
	while (ft_strcmp(command->command.raw, "exit"))
	{
		line = readline(prompt);
		command = cmd_add_unit(command);
		command->command.raw = ft_strdup(line);
		str_edit(&command->command.raw, " ", "");
		printf("Saved to cell %d: {%s}\n", command->id, command->command.raw);
		s_free(&line);
	}
	s_free(&prompt);
	s_free(&command->command.raw);
	db_display_list(sys_l->head);
	cmd_free_list(sys_l->head);
	free(sys_l->head);
	fflush(stdout);
	return ;
}
