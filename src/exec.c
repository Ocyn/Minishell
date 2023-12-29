/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/29 05:07:59 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exe_command(t_execve *cmd, pid_t *fk, char **env)
{
	char	*path;

	path = NULL;
	*fk = fork();
	if (*fk == -1)
		return ;
	if (*fk == 0)
	{
		path = get_path(cmd->one, env);
		execve(path, cmd->full, cmd->env_var);
		perror("bash");
		exit (0);
	}
}

void	stdfdout_dup(pid_t *fk, t_cmd *command, char **env)
{
	dup2(command->outfile, STDOUT_FILENO);
	exe_command(&command->command, fk, env);
	close(command->outfile);
	close(STDOUT_FILENO);
}

void	stdfdin_dup(pid_t *fk, t_cmd *command, char **env)
{
	dup2(command->infile, STDIN_FILENO);
	exe_command(&command->command, fk, env);
	close(command->infile);
	close(STDIN_FILENO);
}

void	pipe_dup(int pipefd[2], pid_t *fk, t_cmd *command, char **env)
{
	close(pipefd[(command->id % 2 + 1)]);
	dup2(pipefd[command->id % 2], command->id % 2);
	exe_command(&command->command, fk, env);
	close(pipefd[command->id % 2]);
}

void	launch_command(t_linux *shell)
{
	t_cmd	*command;
	pid_t	fork_id;
	int		pipefd[2];

	fork_id = 0;
	pipefd[0] = 0;
	pipefd[1] = 0;
	pipe(pipefd);
	(void)command;
	if (!pipefd[0] || !pipefd[1])
		return ;
	command = shell->head;
	// while (command)
	// {
		// 
	// }
	waitpid(fork_id, 0, 0);
	waitpid(fork_id - 1, 0, 0);
}
