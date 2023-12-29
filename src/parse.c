/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/29 13:56:20 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**get_command_args(char **tab)
{
	char	**full;
	int		i;

	i = 0;
	full = NULL;
	if (!tab)
		return (NULL);
	while (tab[i] && !str_occur(tab[i], "|") \
	&& !str_occur(tab[i], ">") && !str_occur(tab[i], "<") \
	&& !str_occur(tab[i], "$"))
		i++;
	full = malloc(sizeof(char *) * (i + 1));
	if (!full)
		return (NULL);
	full[i] = NULL;
	i = 0;
	while (tab[i] && !str_occur(tab[i], "|") \
	&& !str_occur(tab[i], ">") && !str_occur(tab[i], "<") \
	&& !str_occur(tab[i], "$"))
	{
		full[i] = ft_strdup(tab[i]);
		i++;
	}
	full[i] = NULL;
	return (full);
}

t_cmd	*build_commands(t_cmd *command, char **token)
{
	int		i;

	i = -1;
	while (token && token[++i])
	{
		printf("\nDB: tab|%d[%s]\n", i, token[i]);
		command = cmd_add_unit(command);
		command->type = command_pattern(token[i][0]);
		if (token[i] && i >= 1 && str_occur(token[i - 1], ">"))
			command->type = OUTFILE_CMD;
		if (token[i] && str_occur(token[i], "<"))
		{
			command->command.full = ft_split(token[i + 1], ' ');
			command->command.one = ft_strdup(command->command.full[0]);
			i += 2;
			command = cmd_add_unit(command);
		}
		command->command.full = get_command_args(token + i);
		command->command.one = ft_strdup(command->command.full[0]);
		if (token[i] && command->command.full)
			i += tablen(command->command.full);
		if (!token[i])
			break ;
	}
	return (command);
}

char	**get_token(char *cmd_in)
{
	char	**tab;
	char	*temp;

	temp = NULL;
	tab = NULL;
	temp = ft_strtrim(cmd_in, "  \0011\0012\0013\0014\0015\t");
	whitespaces_to_space(&temp);
	str_edit(&temp, "<", " < ");
	str_edit(&temp, "<<", " << ");
	str_edit(&temp, ">", " > ");
	str_edit(&temp, ">>", " >> ");
	str_edit(&temp, "|", " | ");
	tab = ft_split(temp, ' ');
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
	shell->nb_history++;
	token = get_token(cmd_in);
	db_tabstr_display(token);
	command = build_commands(shell->head, token);
	/*DEBUG*/ db_display_list(shell->head);
	//launch_command(shell);
	free_tab(token, tablen(token));
	cmd_free_list(shell->head);
}
