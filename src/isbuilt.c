/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuilt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:16:48 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/23 07:14:00 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_builtin(char *cmd_in, t_cmd *cmd, t_env *env, t_linux *shell)
{
	if (ft_strcmp(cmd_in, "cd") == 0)
		ft_cd(shell, cmd->meta.exec_cmd);
	else if (ft_strcmp(cmd_in, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd_in, "env") == 0)
		ft_env(env);
	else if (ft_strcmp(cmd_in, "exit") == 0)
		ft_exit(cmd, shell);
	else if (ft_strcmp(cmd_in, "echo") == 0)
		ft_echo(cmd->meta.exec_cmd);
	else if (ft_strcmp(cmd_in, "unset") == 0)
		ft_unset(cmd, env, NULL);
	else if (ft_strcmp(cmd_in, "export") == 0)
		ft_export(cmd, env);
	else
		return (0);
	return (1);
}
