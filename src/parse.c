/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/26 00:53:05 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_execve	*get_command(char *str, int len, int type, char **env)
{
	t_execve	*command;
	char		**full_c;

	command = NULL;
	full_c = NULL;
	
	return (command);
}

int	chk_command(char *cmd_in, t_linux *shell)
{
	t_cmd	*command;
	int			i;

	i = 0;
	command = &shell->cmd;
	//printf("Arg_nb: %d  ", shell->cmd->command->arg_n);
	while (cmd_in[i])
	{
		command = command_pattern(cmd_in, "<", INFILE_CMD);
			printf("%d:[%s] ", i, command[i]);
		i++;
	}
	printf("\n");
	// if (!set_command(shell))
	// 	return (1);
	printf("fd: in [%d] | out [%d]\n\n", shell->infile, shell->outfile);
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
	chk_command(cmd_in, shell);
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
	shell->infile = 0;
	shell->outfile = 0;
	shell->commands_count = 0;
	shell->cmd_h = NULL;
}
