/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/20 19:24:20 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strtok(char *src, char delim)
{
	int	id;

	id = 0;
	if (src && delim)
	{
		src = ft_strchr(src, delim);
		src += (src && src[0] && src[1]);
		while (src && src[id] && src[id] != delim)
			id++;
		src[id] = 0;
	}
	return (src);
}

int	preliminary(char **entry)
{
	int		i;
	int		pipe_rep;

	i = -1;
	pipe_rep = 0;
	str_edit(entry, "\t", " ");
	str_edit(entry, "\n", " ");
	str_edit(entry, "\v", " ");
	str_edit(entry, "\r", " ");
	str_edit(entry, "<", " < ");
	str_edit(entry, ">", " > ");
	while ((*entry)[++i])
	{
		while ((*entry)[i] && (*entry)[i] == ' ')
			i++;
		pipe_rep += ((*entry)[i] == '|');
		if ((*entry)[i] != '|' && (*entry)[i] != ' ')
			pipe_rep = 0;
		if (pipe_rep >= 2)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	**split_pipeline(char *cmd_in)
{
	char	**tab;
	char	*temp;

	temp = NULL;
	temp = ft_strtrim(cmd_in, "  \n\v\r\t");
	if (preliminary(&temp) == EXIT_FAILURE)
		return (err_parse_token(1), s_free(&temp), NULL);
	str_edit(&temp, "|", " | ");
	tab = multisplit(temp, "|");
	if (is_tab_empty(tab))
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
	if (!raw_prompt || !raw_prompt[0] || is_str_empty(raw_prompt))
		return ;
	if (!ft_strcmp(raw_prompt, "exit"))
		return (ft_exit(shell));
	add_history(raw_prompt);
	shell->token = split_pipeline(raw_prompt);
	if (!shell->token)
		return ;
	command = build_commands(shell->head, shell->token);
	/*DEBUG*/ db_display_list_cmd(shell->head, "\nTotal Memory Data\n", 1);
	change_env_arg(shell->head->next->meta.raw, shell->env);
	//supprimer simples
	//launch_command(shell, NULL);
	free_tab(shell->token, tablen(shell->token));
	db_cmd_free_list(shell->head);
}
