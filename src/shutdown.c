/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:03:34 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/16 18:42:22 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exit_end(int launch, t_linux *shell)
{
	if (launch)
	{
		s_free(&shell->prompt);
		s_free(&shell->oldpwd);
		rl_clear_history();
		free_env(shell->env);
		free(shell->head);
	}
}

void	exit_prompt(int launch, t_linux *shell)
{
	if (launch)
	{
		s_free(&shell->prompt);
		s_free(&shell->oldpwd);
		rl_clear_history();
		free_env(shell->env);
		free(shell->head);
	}
}

void	exit_forkfailure(int launch, t_linux *shell, int *pip, char **path)
{
	if (launch)
	{
		(void)pip;
		close(pip[1]);
		close(pip[0]);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		s_free(&shell->input);
		s_free(&shell->prompt);
		free_tab(shell->token, tablen(shell->token));
		cmd_free_list(shell->head);
		free(shell->head);
		free_env(shell->env);
		s_free(&shell->oldpwd);
		s_free(path);
		exit (EXIT_FAILURE);
	}
}
