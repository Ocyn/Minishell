/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/21 13:31:54 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*set_command_metadatas(t_cmd *cmd, char *token, int *error, t_env *envv)
{
	t_lst	*keys;
	int		redi[2];

	error = 0;
	ft_memset(redi, 0, sizeof(int) * 2);
	cmd->meta.sraw = ft_strdup(token);
	cmd->meta.raw = multisplit(token, " ");
	change_env_arg(cmd->meta.raw, envv);
	keys = lst_tab_to_list(cmd->meta.raw);
	while (keys && keys->next)
	{
		keys = keys->next;
		keys = get_redirection(keys, redi, error);
	}
	if (error)
		return (lst_free_list(keys), cmd);
	cmd->meta.exec_cmd = lst_list_to_tab(lst_go_to(keys, -1));
	lst_free_list(keys);
	cmd->meta.infile = redi[0];
	cmd->meta.outfile = redi[1];
	/* DEBUG */	db_tabstr_display(cmd->meta.exec_cmd, "\tList to tab New", -1);
	return (cmd);
}

t_cmd	*build_commands(t_cmd *command, char **tokens, t_env *envv)
{
	int		i;
	int		error;
	int		input_len;

	/*DEBUG*/	db_printf("Build command\n", FE_UND);
	i = 0;
	error = 0;
	input_len = tablen(tokens);
	while (i <= input_len && tokens && tokens[i])
	{
		/*DEBUG*/	db_tabstr_display(tokens, "\n\n\tToken Input (i)", i);
		command = cmd_add_unit(command);
		command = set_command_metadatas(command, tokens[i], &error, envv);
		if (error || (!command->meta.exec_cmd))
			cmd_rm_unit(command);
		i++;
	}
	return (command);
}
