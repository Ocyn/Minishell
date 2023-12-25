/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 01:43:07 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	chk_command(t_linux *shell)
{
	if (ft_strchr(shell->command, '|'))
		printf("There's a pipe !\n");
	//bin_command(shell);
	shell->exe.path = get_path(shell->command, shell->envi);
	printf("cmd = \"%s\" | path = \"%s\"\n", shell->command, shell->exe.path);
	is_builtin(shell);
	return (0);
}

void	parse(char *cmd_in, t_linux *shell)
{
	if (!cmd_in || !cmd_in[0])
		return ;
	shell->command = ft_strtrim(cmd_in, " ");
	if (!shell->command)
		return ;
	add_history(cmd_in);
	shell->nb_history++;
	chk_command(shell);
	s_free((void *)shell->command);
}

void	struct_init(t_linux *shell, int a_nb, char **a_s, char **genv)
{
	(void)a_nb;
	(void)a_s;
	ft_bzero(shell, sizeof(t_linux));
	shell->envi = NULL;
	shell->command = NULL;
	shell->nb_history = 0;
	shell->history = NULL;
	shell->end = 0;
	shell->envi = genv;
}
