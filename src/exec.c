/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/23 06:30:36 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	s_dup(int fdin, int fdout, int fd_bonus)
{
	if (fd_bonus != -1)
		close(fd_bonus);
	dup2(fdin, fdout);
	close(fdin);
}

void	auto_dup(t_cmd *cmd, t_pipeline *table)
{
	if (cmd->meta.infile > 2)
		dup2(cmd->meta.infile, STDIN_FILENO);
	else if (cmd->next && cmd->meta.infile <= 2)
		s_dup(table->pline[1], STDOUT_FILENO, table->pline[0]);
	else if (cmd->meta.outfile > 2 && !cmd->next)
		s_dup(cmd->meta.outfile, STDOUT_FILENO, -1);
}

void	exe_command(t_pipeline *table, t_cmd *cmd, t_linux *shell)
{
	char	*path;

	path = NULL;
	table->fork_id = fork();
	if (table->fork_id == _F_FAIL)
		return ((void)err_perror(1));
	if (table->fork_id == _F_CHILD)
	{
		auto_dup(cmd, table);
		if (is_builtin(cmd->meta.exec_cmd[0], cmd, shell->env, shell))
			exit_fork(EXIT_SUCCESS, shell, table, &path);
		path = get_path(cmd->meta.exec_cmd[0], shell->env);
		if (path != NULL)
		{
			execve(path, cmd->meta.exec_cmd, shell->envi);
			exit_fork(EXIT_FAILURE, shell, table, &path);
		}
		exit_fork(127, shell, table, &path);
	}
}

int	pipe_tool(int *piipe, int initorclose)
{
	if (initorclose)
	{
		piipe[0] = -1;
		piipe[1] = -1;
		if (pipe(piipe) == -1)
			return (EXIT_FAILURE);
	}
	if (!initorclose)
	{
		if (close(piipe[0]) == -1 && close(piipe[1]) == -1)
			return (EXIT_FAILURE);
		piipe[0] = -1;
		piipe[1] = -1;
	}
	return (EXIT_SUCCESS);
}

void	launch_command(t_linux *shell, t_cmd *cmd)
{
	t_pipeline	table;

	table.fork_id = 0;
	cmd = shell->head->next;
	table.save = dup(STDIN_FILENO);
	let_signal_through();
	while (cmd)
	{
		err_perror(pipe_tool(table.pline, 1));
		exe_command(&table, cmd, shell);
		waitpid(table.fork_id, &g_sign, 0);
		s_close(1, table.pline[1]);
		if (cmd->id > 1 || cmd->next)
			s_dup(table.pline[0], STDIN_FILENO, -1);
		cmd = cmd->next;
	}
	s_dup(table.save, STDIN_FILENO, -1);
	pipe_tool(table.pline, 0);
	waitpid(table.fork_id, &g_sign, 0);
	while (waitpid(-1, &g_sign, 0) != -1)
		;
	s_close(1, table.save);
	change_ret_signal(g_sign);
	create_signal();
}
