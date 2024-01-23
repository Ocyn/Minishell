/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocyn <ocyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/20 14:57:27 by ocyn             ###   ########.fr       */
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

void	db_display_redi(t_redi redi, char *message)
{
	printf("\t\t%s%s : %s", FE_BOL, message, FRR);
	printf("\n\t\t\tToken : [%s]", redi.token);
	printf("\n\t\t\tFd : [%d]", redi.fd);
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
		db_display_redi(list->infile, "Infile");
		db_display_redi(list->outfile, "Outfile");
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
	command->command.sraw = ft_strdup(line);
	command->command.prefixes = ft_split(line, ' ');
	heredoc = get_heredoc(command->command.sraw);
	if (heredoc)
	{
		insert_tab_in_tab(heredoc, &command->command.args, find_str_in_tab(0, "<<", command->command.args) + 1);
		free_tab(heredoc, tablen(heredoc));
	}
	printf("\n\tSaved to cell %d: [%s] ", command->id, command->command.sraw);
	db_tabstr_display(command->command.prefixes, "\n\tPrefixes\t", -1);
	printf("\n\n");
	syst->command = command;
}

void	db_debug(void)
{
	t_linux	safesystem;

	init_struct(&safesystem);
	safesystem.prompt = prompt_tuning("##SafeMode_Minishell |", "#", "FE_REV FE_BOL");
	read_prompt(&safesystem, "##", safemode_parse);
	s_free(&safesystem.prompt);
	db_display_list(safesystem.head, "\nSafe System: ");
	cmd_free_list(safesystem.head);
	free(safesystem.head);
	return ;
}
