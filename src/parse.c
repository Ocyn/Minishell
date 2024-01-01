/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/01 01:35:30 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**get_token(char *cmd_in, char prime_quote)
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
	if (ft_strchr(temp, '\"'))
		prime_quote = DOUBLEQUOTE;
	printf("\n\tPrimequote = %d | %c  \n", prime_quote, prime_quote);
	tab = split_command(temp, ' ', prime_quote);
	s_free(&temp);
	return (tab);
}

void	parse(char *cmd_in, t_linux *shell)
{
	t_cmd	*command;
	char	**token;
	char	prime_quote;

	command = shell->head;
	token = NULL;
	prime_quote = SIMPLEQUOTE;
	(void)command;
	if (!cmd_in || !cmd_in[0] || is_empty(cmd_in))
		return ;
	if (!ft_strcmp(cmd_in, "exit"))
		return (ft_exit(shell));
	add_history(cmd_in);
	token = get_token(cmd_in, prime_quote);
	/*DEBUG*/ db_tabstr_display(token);
	command = build_commands(shell->head, (const char **)token);
	/*DEBUG*/ db_display_list(shell->head);
	//launch_command(shell);
	free_tab(token, tablen(token));
	cmd_free_list(shell->head);
}
