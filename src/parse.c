/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/29 04:19:19 by jcuzin           ###   ########.fr       */
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

t_cmd	*get_command(t_cmd	*command, char *str, int index)
{
	char	*temp;

	temp = NULL;
	if (!str)
		return (command);
	temp = ft_substr(str, index, (ft_strlen(str) + 1) - index);
	/*DEBUG*/ printf("Command %d saved[%p]:", command->id, command);
	command->type = command_pattern(str[index]);
	command->command.raw = ft_strtrim(str, "  \0011\0012\0013\0014\0015\t");
	s_free(&temp);
	command->command.full = ft_split(command->command.raw, command->type);
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
		if (command_pattern(cmd_in[i]))
		{
			cmd_c++;
			command = cmd_add_unit(command);
			command = get_command(command, cmd_in, i);
			if (cmd_c == 1)
				printf("\nMany command\n");
		}
		i++;
	}
	i = 0;
	if (!cmd_c)
	{
		printf("One command\n");
		command = cmd_add_unit(command);
		printf("\nWho's %d ? [%p]\n", command->id, command);
		command = get_command(command, cmd_in, 0);
	}
	printf("\nList Resume:\n");
	db_display_list(shell->head);
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
	cmd_free_list(shell->head->next);
	free(shell->head->next);
}
