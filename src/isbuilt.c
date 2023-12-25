/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuilt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:16:48 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 05:23:58 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && (str[i] < 9 || str[i] > 13))
			return (0);
		i++;
	}
	return (1);
}

int	is_builtin(t_linux *shell)
{
	if (!ft_strcmp(shell->exe.f_cmd[0], "cd") || !ft_strcmp(shell->exe.f_cmd[0], "pwd") \
	|| !ft_strcmp(shell->exe.f_cmd[0], "exit") || !ft_strcmp(shell->exe.f_cmd[0], "env"))
		return (printf("%s is a built in command !\tSkipped\n", shell->command), 1);
	// if (!ft_strcmp(shell->command, "cd"))
	// 	ft_cd(shell->history[shell->nb_history - 1]);
	// else if (!ft_strcmp(shell->command, "pwd"))
	// 	ft_pwd();
	// else if (!ft_strcmp(shell->command, "exit"))
	// 	ft_exit(shell);
	// else if (!ft_strcmp(shell->command, "env"))
	// 	ft_env(shell);
	// else if (is_empty(shell->command))
	// 	return (1);
	return (0);
}
