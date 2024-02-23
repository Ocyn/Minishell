/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:29 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/23 06:25:49 by jcuzin           ###   ########.fr       */
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

void	exit_fork(int sig, t_linux *shell, t_pipeline *tbl, char **path)
{
	if (sig != 127)
		err_perror(sig);
	s_close(1, tbl->pline[0]);
	s_close(1, tbl->pline[1]);
	s_close(1, tbl->save);
	s_free(&shell->input);
	s_free(&shell->prompt);
	free_tab(shell->token, tablen(shell->token));
	cmd_free_list(shell->head);
	free(shell->head);
	free_env(shell->env);
	s_free(&shell->oldpwd);
	s_free(path);
	exit (sig);
}
