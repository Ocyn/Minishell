/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/26 09:20:04 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*get_command(char *str, int index, char **env)
{
	t_cmd	*command;
	char	*temp;

	(env)
	temp = NULL;
	command = NULL;
	if (!command)
		return (NULL);
	command->type = command_pattern(str[index]);
	return (command);
}

int	clean_command(char *cmd_in, t_linux *shell)
{
	t_cmd	*command;
	int		cmd_c;
	int		i;

	i = 0;
	cmd_c = 0;
	command = &shell->cmd;
	while (cmd_in && cmd_in[i])
	{
		if (command_pattern(cmd_in[i]))
			cmd_c++;
		i++;
	}
	i = 0;
	
	printf("%d:[%s] ", i, command[i]);
	printf("\n");
	exit (0);
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
	exec_all(shell);
}

void	struct_init(t_linux *shell, int a_nb, char **a_s, char **genv)
{
	(void)a_nb;
	(void)a_s;
	ft_bzero(shell, sizeof(t_linux));
	shell->envi = NULL;
	shell->nb_history = 0;
	shell->history = NULL;
	shell->end = 0;
	shell->envi = genv;
	shell->count_cmd = 0;
	shell->cmd_h = NULL;
}
