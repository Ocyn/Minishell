/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/03 01:59:03 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**get_token(char *cmd_in)
{
	char	**tab;
	char	*temp;

	temp = NULL;
	tab = NULL;
	temp = ft_strtrim(cmd_in, "  \0011\0012\0013\0014\0015\t");
	whitespaces_to_space(&temp);
	str_edit(&temp, "<", " < ");
	str_edit(&temp, "<  <", " << ");
	str_edit(&temp, ">", " > ");
	str_edit(&temp, ">  >", " >> ");
	str_edit(&temp, "|", " | ");
	printf("\n\tDebug split_command\n");
	tab = split_command(temp, ' ');
	s_free(&temp);
	return (tab);
}

void	parse(char *cmd_in, t_linux *shell)
{
	t_cmd	*command;
	char	**token;

	command = shell->head;
	token = NULL;
	(void)command;
	if (!cmd_in || !cmd_in[0] || is_empty(cmd_in))
		return ;
	if (!ft_strcmp(cmd_in, "exit"))
		return (ft_exit(shell));
	add_history(cmd_in);
	token = get_token(cmd_in);
	printf("\n\tToken: ");
	/*DEBUG*/ db_tabstr_display(token);
	printf("\n");
	command = build_commands(shell->head, (const char **)token);
	/*DEBUG*/ db_display_list(shell->head);
	//launch_command(shell);
	free_tab(token, tablen(token));
	cmd_free_list(shell->head);
}
