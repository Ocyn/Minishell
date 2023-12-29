/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/29 08:11:49 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!white_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	pipe_splitter(t_cmd **entry)
{
	t_cmd	*src;
	t_cmd	*command;
	char	*temp;
	int		i;
	int		len;

	command = NULL;
	len = 0;
	i = -1;
	command = *entry;
	if (!command || !command->next)
		return (0);
	if (command->id == 0)
		command = command->next;
	src = command;
	len = str_occur(src->command.raw, "|");
	while (++i < len)
	{
		command = cmd_add_unit(command);
		temp = ft_strdup(src->command.full[i]);
		str_edit(&temp, "\t", " ");
		str_edit(&temp, "\0011", " ");
		str_edit(&temp, "\0012", " ");
		str_edit(&temp, "\0013", " ");
		str_edit(&temp, "\0014", " ");
		str_edit(&temp, "\0015", " ");
		command->command.full = ft_split(temp, ' ');
		command->command.one = ft_strdup(command->command.full[0]);
		command->type = PIPE_CMD;
		command->id--;
		s_free(&temp);
	}
	command->type = 0;
	cmd_rm_unit(src);
	return (1);
}

t_cmd	*get_command(t_cmd	*command, char *str, int index)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = -1;
	if (!str)
		return (command);
	/*DEBUG*/ printf("Command %d saved[%p]:\n", command->id, command);
	command->type = command_pattern(str[index]);
	command->command.raw = ft_strtrim(str, "  \0011\0012\0013\0014\0015\t");
	command->command.full = ft_split(command->command.raw, command->type);
	while (command->command.full[++i])
	{
		temp = ft_strdup(command->command.full[i]);
		s_free(&command->command.full[i]);
		command->command.full[i] = ft_strtrim(temp, "  \0011\0012\0013\0014\0015\t");
		s_free(&temp);
	}
	command->command.one = ft_strdup(command->command.full[0]);
	return (command);
}

int	store_command(t_cmd	*command, char *cmd_in, t_linux *shell)
{
	int		cmd_c;
	int		i;

	i = 0;
	cmd_c = 0;
	while (cmd_in && cmd_in[i])
	{
		if (command_pattern(cmd_in[i]) != SINGLE_CMD)
		{
			cmd_c++;
			command = cmd_add_unit(command);
			command = get_command(command, cmd_in, i);
		}
		i++;
	}
	i = 0;
	if (!cmd_c)
	{
		command = cmd_add_unit(command);
		command = get_command(command, cmd_in, 0);
	}
	/*DEBUG*/ db_display_list(shell->head);
	return (0);
}

void	parse(char *cmd_in, t_linux *shell)
{
	t_cmd	*command;

	command = shell->head;
	if (!cmd_in || !cmd_in[0] || is_empty(cmd_in))
		return ;
	if (!ft_strcmp(cmd_in, "exit"))
		return (ft_exit(shell));
	add_history(cmd_in);
	shell->nb_history++;
	store_command(command, cmd_in, shell);
	//launch_command(shell);
	cmd_free_list(shell->head);
}
