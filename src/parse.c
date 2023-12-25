/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 06:51:46 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	chk_command(t_linux *shell)
{
	printf("DB:\tArgs: ");
	if (shell->exe.f_cmd[1])
		printf("Yes [%d]\t", shell->exe.arg_n);
	else
		printf("No\t");
	shell->exe.path = get_path(shell->exe.f_cmd[0], shell->envi);
	printf("In = \"%s\"\tPath = \"%s\"\n", shell->command, shell->exe.path);
	return (0);
}

void	parse(char *cmd_in, t_linux *shell)
{
	if (!cmd_in || !cmd_in[0])
		return ;
	if (is_builtin(cmd_in, shell))
		return ;
	shell->exe.f_cmd = ft_split(cmd_in, ' ');
	shell->command = shell->exe.f_cmd[0];
	if (!shell->command)
		return ;
	shell->exe.arg_n = tablen(shell->exe.f_cmd);
	add_history(cmd_in);
	shell->nb_history++;
	chk_command(shell);
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
