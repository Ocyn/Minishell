/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/03 19:56:20 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*build_commands(t_cmd *command, const char **token)
{
	int		i;
	int		token_len;

	i = 0;
	token_len = tablen((char **)token);
	while (i <= token_len && token && token[i])
	{
		command = chk_infile(command, &i, token);
		command->type = command_pattern(token[i - (i > 0)]);
		command->command.full = get_command_args(token + i * (i <= token_len));
		command->command.raw = tab_to_str(command->command.full, ' ', 0);
		command->command.one = ft_strdup(token[i * (i <= token_len)]);
		if (find_str_in_str(command->command.one, "<<"))
			i += 2;
		else
			i += tablen(command->command.full);
		if (command->prev && command->prev->type == INFILE_CMD)
			command->type = PIPE_CMD;
		if (i > token_len || !token[i])
			break ;
		i++;
	}
	return (command);
}

t_cmd	*chk_infile(t_cmd *cmd, int *index, const char **token)
{
	cmd = cmd_add_unit(cmd);
	if (find_str_in_str(token[*index], "<") \
	&& !find_str_in_str(token[*index], "<<"))
	{
		cmd->command.full = ft_split(token[*index + (token[*index + 1] \
		!= NULL)], ' ');
		cmd->command.raw = tab_to_str(cmd->command.full, ' ', 0);
		cmd->command.one = ft_strdup(cmd->command.full[0]);
		cmd->type = INFILE_CMD;
		*index += 2;
		cmd = cmd_add_unit(cmd);
	}
	return (cmd);
}

char	**get_command_args(const char **tab)
{
	char	**full;
	char	**heredoc;
	int		i;

	i = 0;
	full = NULL;
	heredoc = NULL;
	if (!tab || !tab[0] || command_pattern(tab[0]))
		return (NULL);
	while (tab[i] && !command_pattern(tab[i]))
		i++;
	full = s_malloc(sizeof(char *) * (i + 1));
	if (!full)
		return (NULL);
	i = -1;
	while (tab[++i] && !command_pattern(tab[i]))
		full[i] = ft_strdup(tab[i]);
	heredoc = new_heredoc((char *)full[find_str_in_tab(0, "<<", full)]);
	if (heredoc)
	{
		insert_tab_in_tab(heredoc, &full, find_str_in_tab(0, "<<", full) + 1);
		free_tab(heredoc, tablen(heredoc));
	}
	return (full);
}
