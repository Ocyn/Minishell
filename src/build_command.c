/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/18 23:23:48 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*rm_quotes(char *data, char quote)
{
	char	*new;
	int		len;

	len = 0;
	new = NULL;
	if (!data || !data[0] || !quote || data[0] != quote)
		return (data);
	len = ft_strlen(data);
	new = ft_substr(data, 1, len - ((len > 0) * 2));
	if (!new)
		return (data);
	s_free(&data);
	return (new);
}

t_lst	*get_redirection(t_lst *list, int *redi)
{
	db_print_custom_font("\n\nGet_Redirection\n", FE_BOL);
	if (((char *)list->data)[0] != '>' && ((char *)list->data)[0] != '<')
		return (list);
	token_format(list, redi, _TOK_INFILE, set_infile);
	token_format(list, redi, _TOK_HEREDOC, set_infile);
	token_format(list, redi, _TOK_OUTFILE, set_outfile);
	token_format(list, redi, _TOK_OUTFILE_APP, set_outfile);
	return (list);
}

t_cmd	*set_command_metadatas(t_cmd *cmd, char *token)
{
	t_lst	*keys;
	int		redi[2];

	ft_memset(redi, 0, sizeof(int) * 2);
	cmd->meta.sraw = ft_strdup(token);
	cmd->meta.raw = multisplit(token, " ");
	keys = lst_tab_to_list(cmd->meta.raw);
	db_display_list(keys, "keys of cmd");
	while (keys->next)
	{
		keys = keys->next;
		keys->data = rm_quotes((char *)keys->data, '\"');
		keys = get_redirection(keys, redi);
	}
	cmd->meta.infile = redi[0];
	cmd->meta.outfile = redi[1];
	keys = lst_go_to(keys, -1);
	db_display_list(keys, "New keys of cmd");
	cmd->meta.exec_cmd = lst_list_to_tab(keys);
	db_tabstr_display(cmd->meta.exec_cmd, "List to tab New", -1);
	db_lst_free_list(keys, "Key Of CMD");
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
 