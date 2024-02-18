/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/18 06:48:51 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_lst	*tab_to_list(char **tab)
{
	t_lst	*list;
	t_lst	*head;

	head = lst_init();
	list = head;
	while (tab && tab[0] && tab[0][0])
	{
		if (list->id == 0)
			list = lst_add(head);
		else
			list = lst_add(list);
		list->data = ft_strdup(tab[0]);
		tab++;
	}
	return (head);
}

int	find_str_in_list(t_lst *list_input, char *key)
{
	t_lst	*list;

	list = list_input;
	if (!list || !key)
		return (-1);
	while (list)
	{
		if (find_str_in_str((char *)list->data, key) != -1)
			return (list->id);
		list = list->next;
	}
	return (-1);
}

int	get_type(t_lst *list)
{
	int		type;

	type = _TOK_EMPTY;
	if (!list || !list->data)
		return (type);
	if (find_str_in_str((char *)list->data, "<") != -1)
	{
		type = _TOK_INFILE;
		if (find_str_in_str((char *)list->data, "<<") != -1)
			type = _TOK_HEREDOC;
		if (ft_strlen((char *)list->data) > 1)
			str_edit((char **)(&list->data), "<", "");
	}
	if (find_str_in_str((char *)list->data, ">") != -1)
	{
		type = _TOK_OUTFILE;
		if (find_str_in_str((char *)list->data, ">>") != -1)
			type = _TOK_OUTFILE_APPEND;
		if (ft_strlen((char *)list->data) > 1)
			str_edit((char **)(&list->data), ">", "");
	}
	return (type);
}

t_cmd	*get_redirection(t_cmd *cmd, t_lst *list)
{
	int		err;

	err = 0;
	db_print_custom_font("\n\nGet_Redirection\n", FE_BOL);
	db_display_list(list, "Key_words", 's');
	while (list && !err)
	{
		if (list->id > 0)
		{
			if (get_type(list) == _TOK_INFILE)
				err += set_infile((char *)list->next->data \
				, &cmd->meta.infile, 0);
			if (get_type(list) == _TOK_OUTFILE)
				err += set_outfile((char *)list->next->data \
				, &cmd->meta.infile, 0);
			if (get_type(list) == _TOK_OUTFILE_APPEND)
				err += set_outfile((char *)list->next->data \
				, &cmd->meta.infile, 1);
		}
		list = list->next;
	}
	return (cmd);
}

t_cmd	*set_command_metadatas(t_cmd *cmd, char *token)
{
	t_lst	*key_words;
	t_lst	*head;

	cmd->meta.sraw = ft_strdup(token);
	cmd->meta.raw = multisplit(token, " ");
	head = tab_to_list(cmd->meta.raw);
	key_words = head->next;
	(void)key_words;
	//Infile & outfile include function
	cmd = get_redirection(cmd, head);
	db_lst_free_list(head, 0, "Key_Words");
	return (cmd);
}

t_cmd	*build_commands(t_cmd *command, char **tokens)
{
	int		i;
	int		input_len;

	/*DEBUG*/	db_print_custom_font("Build command\n", FE_UND);
	i = 0;
	input_len = tablen(tokens);
	while (i <= input_len && tokens && tokens[i])
	{
		/*DEBUG*/	db_tabstr_display(tokens, "\n\tToken Input (i)", i);
		command = cmd_add_unit(command);
		command = set_command_metadatas(command, tokens[i]);
		if (!command->meta.exec_cmd && !command->meta.raw)
			cmd_rm_unit(command);
		i++;
		/*DEBUG*/	db_print_custom_font("\n\tEnd loop\t: ", FE_BOL);
		/*DEBUG*/	printf("i [%d] | input_len [%d]\n", i, input_len);
	}
	return (command);
}
