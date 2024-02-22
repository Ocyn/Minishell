/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/22 11:45:39 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exe_command(t_pipeline *table, int b_fd, char **command, t_linux *shell)
{
	char	*path;

	path = NULL;
	table->fork_id = fork();
	if (table->fork_id == -1)
		return ((void)err_perror(1));
	if (table->fork_id == 0)
	{
		dup2(table->pipchild[b_fd], b_fd);
		close(table->pipchild[b_fd]);
		path = get_path(command[0], shell->env);
		if (path != NULL)
		{
			execve(path, command, shell->envi);
			exit_forkfailure(EXIT_FAILURE, shell, table->pipchild, &path);
		}
		exit_forkfailure(127, shell, table->pipchild, &path);
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
		dup2(cmd->meta.infile, table->pipchild[0]);
		if (cmd->meta.infile)
			dup2(cmd->meta.infile, table->pipchild[0]);
		if (cmd->meta.outfile)
			dup2(cmd->meta.outfile, table->pipchild[1]);
		/*DEBUG*/	printf("\t\tpiproot[0][1]: [%d] [%d]\n", table->piproot[0], table->piproot[1]);
		/*DEBUG*/	printf("\t\tpipchild[0][1]: [%d] [%d]\n", table->pipchild[0], table->pipchild[1]);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	launch_command(t_linux *shell, t_cmd *cmd)
{
	t_pipeline	table;

	/*DEBUG*/	db_printf("\nLaunch Command\n\n\n", FE_UND);
	table.fork_id = 0;
	if (err_perror((pipe_tool(table.piproot, 1) || pipe_tool(table.pipchild, 1))))
		return ;
	let_signal_through();
	cmd = shell->head->next;
	while (cmd && cmd->meta.exec_cmd && !select_dup(&table, cmd))
	{
		if (!is_builtin(cmd->meta.exec_cmd[0], shell))
		{
			/*DEBUG*/	db_printf("\n\nOUTPUT START\n\n", FE_BOL);
			exe_command(&table, cmd->id % 2, cmd->meta.exec_cmd, shell);
			/*DEBUG*/	db_printf("\n\nOUTPUT END\n\n", FE_BOL);
			waitpid(table.fork_id, &g_sign, 0);
		}
		cmd = cmd->next;
	}
	err_perror((pipe_tool(table.piproot, 0) || pipe_tool(table.pipchild, 0)));
	change_ret_signal(g_sign);
	create_signal();
}
