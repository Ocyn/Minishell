/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/03 04:54:49 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_tabstr_display(char **tab)
{
	int	i;

	i = -1;
	printf("|");
	while (tab && tab[++i])
		printf(" [%s]", tab[i]);
	printf(" |");
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

void	sfm_parse(char *line, t_linux *syst)
{
	t_cmd	*command;

	command = syst->command;
	command = cmd_add_unit(command);
	command->command.raw = ft_strdup(line);
	str_edit(&command->command.raw, " ", "");
	printf("Saved to cell %d: {%s}\n", command->id, command->command.raw);
}

void	db_debug(void)
{
	t_linux	safesystem;

	struct_init(&safesystem);
	safesystem.prompt = prompt_tuning("##SafeMode_Minishell |", "#", "FE_REV BN_GRA FE_BOL");
	read_prompt(&safesystem, "##", sfm_parse);
	s_free(&safesystem.prompt);
	db_display_list(safesystem.head);
	cmd_free_list(safesystem.head, 0);
	fflush(stdout);
	return ;
}
