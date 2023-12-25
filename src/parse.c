/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 10:48:33 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	chk_command(t_linux *shell)
{
	char	**command;
	int		i;

	i = 0;
	command = shell->exe.f_cmd;
	printf("Arg_nb: %d  ", shell->exe.arg_n);
	while (command[i])
	{
		printf("%d:[%s] ", i, command[i]);
		i++;
	}
	printf("\n");
	if (!set_command(shell))
		return (1);
	printf("fd: in [%d] | out [%d]\n\n", shell->exe.infile, shell->exe.outfile);
	return (0);
}

void	parse(char *cmd_in, t_linux *shell)
{
	if (!cmd_in || !cmd_in[0])
		return ;
	if (!ft_strcmp(cmd_in, "exit"))
	 	return(ft_exit(shell));
	shell->exe.arg_n = 0;
	shell->exe.f_cmd = ft_split(cmd_in, ' ');
	shell->command = shell->exe.f_cmd[0];
	if (!shell->command)
		return ;
	shell->exe.arg_n = tablen(shell->exe.f_cmd);
	add_history(cmd_in);
	shell->nb_history++;
	chk_command(shell);
	exec_all(shell);
	if (shell->exe.infile)
		close(shell->exe.infile);
	if (shell->exe.outfile)
		close(shell->exe.outfile);
	s_free(&shell->exe.path);
	free_tab(shell->exe.f_cmd, shell->exe.arg_n);
}

void	struct_init(t_linux *shell, int a_nb, char **a_s, char **genv)
{
	(void)a_nb;
	(void)a_s;
	ft_bzero(shell, sizeof(t_linux));
	shell->envi = NULL;
	shell->exe.f_cmd = NULL;
	shell->nb_history = 0;
	shell->history = NULL;
	shell->end = 0;
	shell->envi = genv;
}
