/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuilt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:16:48 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/06 05:51:59 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_builtin(char *cmd_in, t_linux *shell)
{
	if (ft_strcmp(cmd_in, "cd") == 0)
		ft_cd(shell, shell->head->next->meta.exec_cmd);
	else if (ft_strcmp(cmd_in, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd_in, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(cmd_in, "exit") == 0)
		ft_exit(shell);
	else if (ft_strcmp(cmd_in, "echo") == 0)
		ft_echo(shell->head->next->meta.exec_cmd);
	else if (ft_strcmp(cmd_in, "unset") == 0)
		ft_unset(shell, NULL);
	else if (ft_strcmp(cmd_in, "export") == 0)
		ft_export(shell);
	else
		return (0);
	return (1);
}
