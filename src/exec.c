/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/22 19:26:22 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	smart_dup(t_pipeline *table, t_cmd *cmd, int id)
{
	(void)cmd;
	if (cmd->id == 1 && !cmd->next)
		return ;
	close(table->pline[(id + 1) % 2]);
	dup2(table->pline[id % 2], id % 2);
	close(table->pline[(id) % 2]);
}

void	exe_command(t_pipeline *table, t_cmd *cmd, t_linux *shell)
{
	char	*path;
	int		b_fd;

	b_fd = cmd->id;
	path = NULL;
	table->fork_id = fork();
	if (table->fork_id == -1)
		return ((void)err_perror(1));
	if (table->fork_id == 0)
	{
		smart_dup(table, cmd, 1);
		path = get_path(cmd->meta.exec_cmd[0], shell->env);
		if (path != NULL)
		{
			execve(path, cmd->meta.exec_cmd, shell->envi);
			exit_forkfailure(EXIT_FAILURE, shell, table->pline, &path);
		}
		exit_forkfailure(127, shell, table->pline, &path);
	}
}

int	pipe_tool(int *piipe, int initorclose)
{
	if (initorclose)
	{
		ft_memset(piipe, -1, 2);
		if (pipe(piipe) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (close(piipe[0]) == -1 || close(piipe[1]) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	select_dup(t_pipeline *table, t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->meta.infile)
			dup2(cmd->meta.infile, table->pline[0]);
		if (cmd->meta.outfile)
			dup2(cmd->meta.outfile, table->pline[1]);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	launch_command(t_linux *shell, t_cmd *cmd)
{
	t_pipeline	table;

	table.fork_id = 0;
	err_perror(pipe_tool(table.pline, 1));
	let_signal_through();
	cmd = shell->head->next;
	while (cmd && cmd->meta.exec_cmd)
	{
		if (!is_builtin(cmd->meta.exec_cmd[0], cmd, shell->env, shell))
			exe_command(&table, cmd, shell);
		cmd = cmd->next;
	}
	cmd = shell->head->next;
	err_perror(pipe_tool(table.pline, 0));
	while (cmd && cmd->meta.exec_cmd)
	{
		waitpid(-1, &g_sign, 0);
		cmd = cmd->next;
	}
	change_ret_signal(g_sign);
	create_signal();
}
