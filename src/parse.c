/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/06 09:26:07 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	whitespaces_to_space(char **entry)
{
	str_edit(entry, "\t", " ");
	str_edit(entry, "\n", " ");
	str_edit(entry, "\v", " ");
	str_edit(entry, "\r", " ");
}

char	**get_token(char *cmd_in)
{
	char	**tab;
	char	*temp;

	temp = NULL;
	temp = ft_strtrim(cmd_in, "  \n\v\r\t");
	whitespaces_to_space(&temp);
	str_edit(&temp, ">", " > ");
	str_edit(&temp, ">  >", " >> ");
	str_edit(&temp, "<", " < ");
	str_edit(&temp, "<  <", " << ");
	str_edit(&temp, "|", " | ");
	tab = multisplit(temp, "|");
	//commande de nono
	s_free(&temp);
	return (tab);
}

void	parse(t_linux *shell)
{
	t_cmd	*command;
	char	*cmd_in;
	char	**token;

	(void)command;
	command = shell->head;
	token = NULL;
	cmd_in = shell->input;
	if (!cmd_in || !cmd_in[0] || is_empty(cmd_in))
		return ;
	if (!ft_strcmp(cmd_in, "exit"))
		return (ft_exit(shell));
	add_history(cmd_in);
	token = get_token(cmd_in);
	command = build_commands(shell->head, token);
	shell->token = token;
	/*DEBUG*/ db_display_list(shell->head, "\nTotal Memory Data\n");
	//launch_command(shell);
	free_tab(token, tablen(token));
	db_cmd_free_list(shell->head);
}

void	change_oldpwd(t_linux *shell)
{
	if (shell->oldpwd)
		s_free(&shell->oldpwd);
	shell->oldpwd = getcwd(NULL, 0);
}
