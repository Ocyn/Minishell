/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 07:53:15 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_print_custom_font(char *message, char *font_effect)
{
	if (font_effect)
		printf("%s", font_effect);
	if (message)
		printf("%s", message);
	if (font_effect)
		printf("%s", FRR);
}

void	db_tabstr_display(char **tab, char *message, int highlight)
{
	int	i;

	i = -1;
	db_print_custom_font(message, FE_BOL);
	db_print_custom_font(" : ", FE_BOL);
	printf("|");
	if (!tab || !tab[i + 1])
			printf(" "HIGHLIGHT_TEXT"[Empty]"FONT_RESET"");
	while (tab && tab[++i])
	{
		if (i == highlight)
			printf(" [%d "HIGHLIGHT_TEXT"[%s]"FONT_RESET"", highlight, tab[i]);
		else
			printf(" [%s]", tab[i]);
	}
	if (tab && i == highlight)
		printf(" [%d "HIGHLIGHT_TEXT"[End]"FONT_RESET"", highlight);
	printf(" |");
}

void	db_display_list(t_cmd *list, char *message)
{
	db_print_custom_font(message, FE_UND);
	printf("\n");
	if (list->next)
	{
		printf("\t"FE_REV""FE_BOL"Cell %d"FRR" [%p]: HEAD\n\n", list->id, list);
		list = list->next;
	}
	while (list)
	{
		printf("\t"FE_REV""FE_BOL"Cell %d"FRR" [%p]:\n", list->id, list);
		db_print_custom_font("\t\tType :", FE_BOL);
		printf("\t[%d]_", list->type);
		if (list->type == SINGLE_CMD)
			printf("COMMAND\n");
		else if (list->type == PIPE_CMD)
			printf("PIPE\n");
		else if (list->type == DOLLARSIGN_CMD)
			printf("DOLLARSIGN\n");
		else if (list->type == INFILE_CMD)
			printf("INFILE\n");
		else if (list->type == OUTFILE_CMD)
			printf("OUTFILE\n");
		else if (list->type == HEREDOC)
			printf("HEREDOC\n");
		else if (list->type == OUTFILE_ADDER)
			printf("OUTFILE_ADDER\n");
		else if (list->type == EMPTY_CMD)
			printf("EMPTY\n");
		else
			printf("UNKNOWN\n");
		db_tabstr_display(list->command.raw, "\t\tRaw", -1);
		printf("\n");
		db_tabstr_display(list->command.prefixes, "\t\tPrefixes", -1);
		printf("\n");
		db_tabstr_display(list->command.args, "\t\tArgs", -1);
		printf("\n");
		db_print_custom_font("\t\tPrev :", FE_BOL);
		printf("\t[%p]\n", list->prev);
		db_print_custom_font("\t\tNext :", FE_BOL);
		printf("\t[%p]\n", list->next);
		if (list->next)
			list = list->next;
		else
			break ;
	}
	printf("\n");
}

void	safemode_parse(t_linux *syst)
{
	t_cmd	*command;
	char	**heredoc;
	char	*line;

	heredoc = NULL;
	command = syst->command;
	line = syst->input;
	command = cmd_add_unit(command);
	command->command.raw[0] = ft_strdup(line);
	command->command.prefixes = ft_split(line, ' ');
	heredoc = new_heredoc(command->command.raw[0], 0);
	if (heredoc)
	{
		insert_tab_in_tab(heredoc, &command->command.args, find_str_in_tab(0, "<<", command->command.args) + 1);
		free_tab(heredoc, tablen(heredoc));
	}
	printf("\n\tSaved to cell %d: [%s] ", command->id, command->command.raw[0]);
	db_tabstr_display(command->command.prefixes, "\n\tPrefixes\t", -1);
	printf("\n\n");
	syst->command = command;
}

void	db_debug(void)
{
	t_linux	safesystem;

	struct_init(&safesystem);
	safesystem.prompt = prompt_tuning("##SafeMode_Minishell |", "#", "FE_REV FE_BOL");
	read_prompt(&safesystem, "##", safemode_parse);
	s_free(&safesystem.prompt);
	db_display_list(safesystem.head, "\nSafe System: ");
	cmd_free_list(safesystem.head);
	free(safesystem.head);
	return ;
}
