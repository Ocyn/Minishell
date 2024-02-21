/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/21 13:29:19 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	token_repetition(char *str, char token, int max_rep)
{
	int	id;
	int	rep_count;
	int	state;

	id = -1;
	state = (str && str[0] == '|');
	rep_count = 0;
	if (!ft_strchr(str, token))
		return (EXIT_SUCCESS);
	while (str && str[++id])
	{
		while (str[id] && str[id] == ' ')
			id++;
		state = (str[id] == '|');
		if (str[id] != '|' && str[id] != ' ')
			state = 0;
		rep_count += (str[id] == token);
		if (str[id] != token && str[id] != ' ')
			rep_count = 0;
		if (rep_count >= max_rep)
			return (EXIT_FAILURE);
	}
	if ((token == '|' && state))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	preliminary(char **entry)
{
	if (is_str(*entry, is_white_space) || is_str(*entry, is_special_token))
		return (EXIT_FAILURE);
	str_edit(entry, "\t", " ");
	str_edit(entry, "\n", " ");
	str_edit(entry, "\v", " ");
	str_edit(entry, "\r", " ");
	if (token_repetition(*entry, '|', 2) || token_repetition(*entry, '<', 3) \
	|| token_repetition(*entry, '>', 3))
		return (EXIT_FAILURE);
	if ((*entry)[0] == '|')
		return (EXIT_FAILURE);
	str_edit(entry, "<", " < ");
	str_edit(entry, ">", " > ");
	return (EXIT_SUCCESS);
}

char	**split_pipeline(char *cmd_in)
{
	char	**tab;
	char	*temp;

	temp = NULL;
	temp = ft_strtrim(cmd_in, " \n\v\r\t");
	if (preliminary(&temp) == EXIT_FAILURE)
		return (err_parse_token(1), s_free(&temp), NULL);
	str_edit(&temp, "|", " | ");
	tab = multisplit(temp, "|");
	if (is_tab(tab, is_white_space) || is_tab(tab, is_special_token))
	{
		free_tab(tab, tablen(tab));
		return (err_parse_token(1), s_free(&temp), NULL);
	}
	s_free(&temp);
	return (tab);
}

void	parse(t_linux *shell)
{
	t_cmd	*command;
	char	*raw_prompt;

	(void)command;
	command = shell->head;
	raw_prompt = shell->input;
	if (!raw_prompt || !raw_prompt[0] || is_str(raw_prompt, is_white_space))
		return ;
	if (!ft_strcmp(raw_prompt, "exit"))
		return (ft_exit(shell));
	add_history(raw_prompt);
	shell->token = split_pipeline(raw_prompt);
	if (!shell->token)
		return ;
	command = build_commands(shell->head, shell->token, shell->env);
	/*DEBUG*/ db_display_list_cmd(shell->head, "\nTotal Memory Data\n", 0);
	launch_command(shell, NULL);
	free_tab(shell->token, tablen(shell->token));
	db_cmd_free_list(shell->head);
}
