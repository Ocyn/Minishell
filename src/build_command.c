/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/18 23:49:23 by jcuzin           ###   ########.fr       */
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
	while (keys->next)
	{
		keys = keys->next;
		keys->data = rm_quotes((char *)keys->data, '\"');
		keys = get_redirection(keys, redi);
	}
	cmd->meta.infile = redi[0];
	cmd->meta.outfile = redi[1];
	keys = lst_go_to(keys, -1);
	cmd->meta.exec_cmd = lst_list_to_tab(keys);
	lst_free_list(keys);
	return (cmd);
}

t_cmd	*build_commands(t_cmd *command, char **tokens)
{
	int		i;
	int		input_len;

	i = 0;
	input_len = tablen(tokens);
	while (i <= input_len && tokens && tokens[i])
	{
		command = cmd_add_unit(command);
		command = set_command_metadatas(command, tokens[i]);
		if (!command->meta.exec_cmd && !command->meta.raw)
			cmd_rm_unit(command);
		i++;
	}
	return (command);
}
