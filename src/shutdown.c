/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocyn <ocyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:29 by ocyn              #+#    #+#             */
/*   Updated: 2024/01/17 15:48:03 by ocyn             ###   ########.fr       */
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

void	exit_forkfailure(int launch, t_linux *shell, int *pip)
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
	}
}
