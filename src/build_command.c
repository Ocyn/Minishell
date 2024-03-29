/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/23 01:00:55 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*set_command_metadatas(t_cmd *cmd, char *token, int *err, t_linux *e)
{
	t_lst	*keys;
	int		redi[3];
	t_lst	*start;

	ft_memset(redi, 0, sizeof(int) * 3);
	cmd->meta.sraw = ft_strdup(token);
	cmd->meta.raw = multisplit(token, " ");
	change_env_arg(cmd->meta.raw, e->env);
	keys = lst_tab_to_list(cmd->meta.raw);
	start = keys;
	while (keys && keys->next)
	{
		keys = keys->next;
		keys = get_redirection(keys, redi, e);
	}
	(*err) = redi[2];
	if ((*err))
		return (lst_free_list(start), cmd);
	cmd->meta.exec_cmd = lst_list_to_tab(lst_go_to(keys, -1));
	cmd->meta.infile = redi[0];
	cmd->meta.outfile = redi[1];
	ampute_quotes(cmd->meta.exec_cmd);
	ampute_quotes(cmd->meta.raw);
	lst_free_list(keys);
	return (cmd);
}

t_cmd	*build_commands(t_cmd *command, char **tokens, t_linux *envv)
{
	int		i;
	int		error;
	int		input_len;

	i = 0;
	error = 0;
	input_len = tablen(tokens);
	while (i <= input_len && tokens && tokens[i])
	{
		command = cmd_add_unit(command);
		command = set_command_metadatas(command, tokens[i], &error, envv);
		if (error || (!command->meta.exec_cmd))
		{
			cmd_rm_unit(command);
			return (NULL);
		}
		i++;
	}
	return (command);
}
