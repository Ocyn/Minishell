/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuilt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <<jcuzin@student.42.fr>>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:16:48 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/08 03:44:49 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_builtin(char *cmd_in, t_linux *shell)
{
	(void)shell;
	if (!ft_strcmp(cmd_in, "cd") \
	|| !ft_strcmp(cmd_in, "pwd") || !ft_strcmp(cmd_in, "env"))
		return (printf("%s is a built in command !\tSkipped\n", cmd_in), 1);
	// if (!ft_strcmp(cmd_in, "cd"))
	// 	ft_cd(shell->history[shell->nb_history - 1]);
	// else if (!ft_strcmp(cmd_in, "pwd"))
	// 	ft_pwd();
	// else if (!ft_strcmp(cmd_in, "env"))
	// 	ft_env(shell);
	// else if (is_empty(cmd_in))
	// 	return (1);
	// else if (!ft_strcmp(cmd_in, "exit"))
	// 	return(ft_exit(shell), 1);
	return (0);
}
