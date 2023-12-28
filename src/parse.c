/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/28 20:52:48 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*get_command(t_cmd	*command, char *str, int index, char **env)
{
	char	*temp;

	(void)env;
	temp = NULL;
	if (!str)
		return (command);
	cmd_init(command, NULL, 0);
	temp = ft_substr(str, index, (ft_strlen(str) + 1) - index);
	/*DEBUG*/ printf("Get_CMD:\tIn: [%s] | ", str);
	command->type = command_pattern(str[index]);
	/*DEBUG*/ printf(" | Type: [%c]", command->type);
	command->command.raw = ft_strtrim(str, "  \0011\0012\0013\0014\0015\t");
	/*DEBUG*/ printf(" | Raw: [%s]", command->command.raw);
	s_free(&temp);
	command->command.full = ft_split(command->command.raw, command->type);
	/*DEBUG*/ printf(" | Full: ");
	/*DEBUG*/ db_tabstr_display(command->command.full);
	command->command.one = command->command.full[0];
	/*DEBUG*/ printf(" | One: [%s]", command->command.one);
	command->command.path = get_path(command->command.one, env);
	/*DEBUG*/ printf(" | Path: [%s]\n", command->command.path);
	return (command);
}

int	clean_command(char *cmd_in, t_linux *shell)
{
	t_cmd	*command;
	int		cmd_c;
	int		i;

	i = 0;
	cmd_c = 0;
	command = NULL;
	command = shell->head;
	while (cmd_in && cmd_in[i])
	{
		if (command_pattern(cmd_in[i]))
		{
			cmd_c++;
			command = cmd_add_unit(command);
			command = get_command(command, cmd_in, i, shell->envi);
			command->id = cmd_c - 1;
			if (cmd_c == 1)
			{
				shell->head->next = command;
				printf("Many command\n");
			}
		}
		i++;
	}
	i = 0;
	if (!cmd_c)
	{
		printf("One command\n");
		command = cmd_add_unit(command);
		shell->head->next = command;
		command = get_command(command, cmd_in, 0, shell->envi);
	}
	printf("List\n");
	cmd_display_list(command);
	printf("%d:[%s]\n", i, command->command.raw);
	return (0);
}

void	parse(char *cmd_in, t_linux *shell)
{
	if (!cmd_in || !cmd_in[0])
		return ;
	if (!ft_strcmp(cmd_in, "exit"))
		return (ft_exit(shell));
	add_history(cmd_in);
	shell->nb_history++;
	clean_command(cmd_in, shell);
	//execute command
	cmd_free_list(shell->head->next);
}

void	struct_init(t_linux *shell, int a_nb, char **a_s, char **genv)
{
	(void)a_nb;
	(void)a_s;
	ft_bzero(shell, sizeof(t_linux));
	shell->head = malloc(sizeof(t_cmd));
	if (!shell->head)
		return ;
	cmd_init(shell->head, NULL, 0);
	shell->head->next = NULL;
	shell->head->prev = NULL;
	shell->head->id = 0;
	shell->envi = NULL;
	shell->nb_history = 0;
	shell->history = NULL;
	shell->end = 0;
	shell->envi = genv;
	shell->count_cmd = 0;
}
