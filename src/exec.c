/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/07 16:00:21 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exe_command(t_execve *cmd, pid_t *fk, char **env)
{
	char	*path;

	path = NULL;
	(void)fk;
	// *fk = fork();
	// if (*fk == -1)
	// 	return ;
	// if (*fk == 0)
	// {
		printf("\n\t\t[%s]", cmd->prefixes[0]);
		path = get_path(cmd->prefixes[0], env);
		printf("execve(path[%s] | \n)", path);
		db_tabstr_display(cmd->prefixes, "args", -1);
		printf(" | Env[Too long]\n)");
		// execve(path, cmd->args, env);
		// perror("bash");
		s_free(&path);
		// exit (0);
	// }
}

// void	stdfdout_dup(pid_t *fk, t_cmd *command, char **env)
// {
	
// 	// dup2(command->outfile, STDOUT_FILENO);
// 	// exe_command(&command->command, fk, env);
// 	// close(command->outfile);
// 	// close(STDOUT_FILENO);
// }

// void	stdfdin_dup(pid_t *fk, t_cmd *command, char **env)
// {
// 	// dup2(command->infile, STDIN_FILENO);
// 	// exe_command(&command->command, fk, env);
// 	// close(command->infile);
// 	// close(STDIN_FILENO);
// }

void	select_dup(pid_t *fk, t_cmd *command, char **env)
{
	(void)fk;
	(void)env;
	printf("\n\tRedirect : ");
	if (command->type == INFILE_CMD)
	{
		printf("STDIN -> ");
	}
	if (command->type == OUTFILE_CMD)
	{
		printf("STDOUT -> ");
	}
	if (command->type == PIPE_CMD)
	{
		printf("Output of [%d", command->id);
		db_tabstr_display(command->command.prefixes, "", -1);
	}
	if (command->type == INFILE_CMD && command->type == OUTFILE_CMD)
		db_tabstr_display(command->command.args, "File", -1);
	if (command->type == PIPE_CMD && command->next)
	{
		db_tabstr_display(command->next->command.prefixes, "Input of Next", -1);
	}
}

// void	pipe_dup(int pipefd[2], pid_t *fk, t_cmd *command, char **env)
// {
// 	// close(pipefd[(command->id % 2 + 1)]);
// 	// dup2(pipefd[command->id % 2], command->id % 2);
// 	// exe_command(&command->command, fk, env);
// 	// close(pipefd[command->id % 2]);
// }

void	launch_command(t_linux *shell)
{
	t_cmd	*command;
	pid_t	fork_id;
	int		pipefd[2];

	fork_id = 0;
	pipefd[0] = 0;
	pipefd[1] = 0;
	//pipe(pipefd);
	(void)command;
	//if (!pipefd[0] || !pipefd[1])
		//return ;
	command = shell->head;
	while (command)
	{
		select_dup(&fork_id, command, shell->envi);
		exe_command(&command->command, &fork_id, shell->envi);
		command = command->next;
	}
	//waitpid(fork_id, 0, 0);
	//waitpid(fork_id - 1, 0, 0);
}
