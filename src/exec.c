/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/22 14:28:10 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	smart_dup(t_pipeline *table, t_cmd *cmd, int id)
{
	(void)cmd;
	if (cmd.id == 1 && !cmd->next)
		return ;
	close(table->pline[(id + 1) % 2]);
	dup2(table->pline[id % 2], id % 2);
}

void	exe_command(t_pipeline *table, t_cmd *cmd, t_linux *shell)
{
	char	*path;
	int		b_fd;

	b_fd = cmd->id;
	/*DEBUG*/	printf("\nCommand %d:\n  Close (pipe[%d] => %d)\n", b_fd, (b_fd + 1) % 2, table->pline[(b_fd + 1) % 2]);
	/*DEBUG*/	printf("  dup2 (pipe[%d] => %d, STD_[%d])\n", b_fd % 2, table->pline[b_fd % 2], b_fd % 2);
	/*DEBUG*/	db_printf("\n\nOUTPUT START\n\n", FE_BOL);
	path = NULL;
	table->fork_id = fork();
	if (table->fork_id == -1)
		return ((void)err_perror(1));
	if (table->fork_id == 0)
	{
		smart_dup(table, cmd, b_fd);
		path = get_path(cmd->meta.exec_cmd[0], shell->env);
		if (path != NULL)
		{
			execve(path, cmd->meta.exec_cmd, shell->envi);
			exit_forkfailure(EXIT_FAILURE, shell, table->pline, &path);
		}
		exit_forkfailure(127, shell, table->pline, &path);
	}
	else
		/*DEBUG*/	db_printf("\n\nOUTPUT END\n\n", FE_BOL);
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

	/*DEBUG*/	db_printf("\nLaunch Command\n\n\n", FE_UND);
	table.fork_id = 0;
	err_perror(pipe_tool(table.pline, 1));
	let_signal_through();
	cmd = shell->head->next;
	while (cmd && cmd->meta.exec_cmd)
	{
		if (!is_builtin(cmd->meta.exec_cmd[0], shell))
		{
			exe_command(&table, cmd, shell);
			waitpid(table.fork_id - 1, &g_sign, 0);
		}
		cmd = cmd->next;
	}
	err_perror(pipe_tool(table.pline, 0));
	waitpid(table.fork_id, &g_sign, 0);
	change_ret_signal(g_sign);
	create_signal();
}
