/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:29 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/23 10:43:15 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exit_end(int launch, t_linux *shell)
{
	if (launch)
	{
		close(STDIN_FILENO);
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

void	exit_forkfailure(int launch, t_linux *shell, char **path)
{
	s_free(&shell->input);
	s_free(&shell->prompt);
	free_tab(shell->token, tablen(shell->token));
	cmd_free_list(shell->head);
	close (STDIN_FILENO);
	free(shell->head);
	free_env(shell->env);
	s_free(&shell->oldpwd);
	if (path != NULL)
		s_free(path);
	if (launch >= 0)
		exit (launch);
}

void	exit_fork(int sig, t_linux *shell, t_pipeline *tbl, char **path)
{
	if (sig != 127)
		err_perror(sig);
	if (cmd_len(shell->head->next) > 1)
	{
		s_close(1, tbl->pline[0]);
		s_close(1, tbl->pline[1]);
	}
	s_close(1, tbl->save);
	close (STDIN_FILENO);
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
