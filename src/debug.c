/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/18 19:57:39 by jcuzin           ###   ########.fr       */
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

void	db_display_list(t_lst *list, char *message)
{
	printf("\n%sDisplay [%s%s%s%s] list:%s\n\n", FE_UND, FE_BOL, message, FRR, FE_UND, FRR);
	if (list->next)
	{
		printf("\t"FE_REV""FE_BOL"Cell %d"FRR" [%p]: HEAD\n\n", list->id, list);
		list = list->next;
	}
	while (list)
	{
		printf("\t"FE_REV""FE_BOL"Cell %d"FRR" [%p]:\n", list->id, list);
		db_print_custom_font("\t\tData :", FE_BOL);
		printf("\t[%s]\n", (char *)list->data);
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

void	*db_lst_free_list(t_lst *lst, char *title)
{
	printf("\n%sFree [%s] List:%s\n\n", FE_UND, title, FRR);
	if (lst && lst->prev)
		lst = lst_go_to(lst, -1);
	while (lst)
	{
		printf("\t"FE_REV""FE_BOL"Cell %d"FRR" [%p]: \n", lst->id, lst);
		printf("\t\tData: [%s]", (char *)lst->data);
		s_free((char **)(&lst->data));
		printf("\r\t%s\n", __VALID_FREED);
		if (lst->next)
		{
			lst = lst->next;
			free(lst->prev);
			lst->prev = NULL;
		}
		else
			break ;
	}
	free(lst);
	lst = NULL;
	return (NULL);
}

void	db_display_list_cmd(t_cmd *list, char *message)
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
		db_print_custom_font("\t\tInfile :", FE_BOL);
		printf("\t[%d]\n", list->meta.infile);
		db_print_custom_font("\t\tOutfile :", FE_BOL);
		printf("\t[%d]\n", list->meta.outfile);
		db_print_custom_font("\t\tSraw :", FE_BOL);
		printf("\t[%s]", list->meta.sraw);
		printf("\n");
		db_tabstr_display(list->meta.raw, "\t\tRaw", -1);
		printf("\n");
		db_tabstr_display(list->meta.exec_cmd, "\t\tExec_Cmd", -1);
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

void	*db_cmd_free_list(t_cmd *cmd)
{
	db_print_custom_font("\nFree List\n\n", FE_UND);
	if (cmd->id == 0)
	{
		printf("\t"FE_REV""FE_BOL"Cell %d"FRR" [%p]: HEAD\n\n", cmd->id, cmd);
		cmd = cmd->next;
	}
	while (cmd)
	{
		printf("\t"FE_REV""FE_BOL"Cell %d"FRR" [%p]: \n", cmd->id, cmd);
		db_tabstr_display(cmd->meta.raw, "\t\tRaw", -1);
		free_tab(cmd->meta.raw, tablen(cmd->meta.raw));
		printf("\r\t%s\n", __VALID_FREED);
		db_print_custom_font("\t\tSraw : ", FE_BOL);
		printf("[%s]", cmd->meta.sraw);
		s_free(&cmd->meta.sraw);
		printf("\r\t%s\n", __VALID_FREED);
		if (cmd->meta.exec_cmd)
		{
			db_tabstr_display(cmd->meta.exec_cmd, "\t\texec_cmd", -1);
			free_tab(cmd->meta.exec_cmd, tablen(cmd->meta.exec_cmd));
			printf("\r\t"__VALID_FREED"\n");
		}
		if (cmd->next)
		{
			cmd = cmd->next;
			free(cmd->prev);
			cmd->prev = NULL;
		}
		else
			break ;
	}
	free(cmd);
	cmd = NULL;
	return (NULL);
}

void	safemode_parse(t_linux *syst)
{
	t_cmd	*command;
	char	*line;

	command = syst->command;
	line = syst->input;
	command = cmd_add_unit(command);
	command->meta.exec_cmd= ft_split(line, ' ');
	printf("\n\tSaved to cell %d: ", command->id);
	db_tabstr_display(command->meta.exec_cmd, "\n\tFinal Command\t", -1);
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
	db_display_list_cmd(safesystem.head, "\nSafe System: ");
	cmd_free_list(safesystem.head);
	free(safesystem.head);
	return ;
}
