/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/03 03:06:46 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	heredoc_index_moving(int *heredoc_check, int if_no_heredoc)
{
	if (*heredoc_check)
	{
		*heredoc_check = 0;
		return (2 + (if_no_heredoc == 1));
	}
	else
		return (if_no_heredoc);
}

t_cmd	*build_commands(t_cmd *command, const char **token)
{
	int		i;
	int		token_len;
	int		ifheredoc;

	i = 0;
	ifheredoc = 0;
	token_len = tablen((char **)token);
	while (i <= token_len && token && token[i])
	{
		command = chk_infile(command, &i, token);
		command->command.full = get_command_args(token + i, &ifheredoc);
		command->command.raw = tab_to_str(command->command.full, ' ', 0);
		if (command->command.full)
			command->command.one = ft_strdup(command->command.full[0]);
		command->type = command_pattern(token[i - (i > 0)]);
		i += heredoc_index_moving(&ifheredoc, tablen(command->command.full));
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
	if (find_str_in_str(token[*index], "<") && !heredoc_check(token, *index, NULL))
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

char	**get_command_args(const char **tab, int *ifheredoc)
{
	char	**full;
	int		heredoc;
	int		i;

	i = -1;
	heredoc = -2;
	full = NULL;
	if (!tab || command_pattern(tab[0]))
		return (NULL);
	while (tab[++i] && !command_pattern(tab[i]))
		if (heredoc_check(tab, i, ifheredoc))
			heredoc = i;
	full = s_malloc(sizeof(char *) * (i + 1));
	if (!full)
		return (NULL);
	full[i] = NULL;
	i = -1;
	while (tab[++i] && !command_pattern(tab[i]))
	{
		if (heredoc == i)
			return (heredocument((char *)tab[i + 1], full, i, (char **)tab));
		full[i] = ft_strdup(tab[i]);
	}
	full[i] = NULL;
	return (full);
}
