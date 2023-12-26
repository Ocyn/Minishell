/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/26 08:43:40 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exe_command(t_execve *cmd, pid_t *fk)
{
	*fk = fork();
	if (*fk == -1)
		return ;
	if (*fk == 0)
	{
		execve(cmd->path, cmd->full, cmd->env_var);
		perror("bash");
		exit (0);
	}
}

void	stdfdout_dup(pid_t *fk, t_cmd *command)
{
	dup2(command->outfile, STDOUT_FILENO);
	exe(command->command, fk);
	close(command->outfile);
	close(STDOUT_FILENO);
}

void	stdfdin_dup(pid_t *fk, t_cmd *command)
{
	dup2(command->infile, STDIN_FILENO);
	exe(command->command, fk);
	close(command->infile);
	close(STDIN_FILENO);
}

void	pipe_dup(int pipefd[2], pid_t *fk, t_cmd *command)
{
	close(pipefd[(command->id % 2 + 1)]);
	dup2(pipefd[command->id % 2], command->id % 2);
	exe(command->command, fk);
	close(pipefd[command->id % 2]);
}

void	launch_command(t_linux *shell)
{
	t_cmd	*command;
	pid_t	fork_id;
	int		pipefd[2];

	pipe(&pipefd);
	if (!pipefd)
		return ;
	command = shell->cmd_h;
	while (command->next)
	{
		
	}
	waitpid(fork_id, 0, 0);
	waitpid(fork_id - 1, 0, 0);
}
