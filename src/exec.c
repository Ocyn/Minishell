/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/21 15:41:14 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exe_command(t_cmd *cmd, pid_t *fk, int *pip, t_linux *shell)
{
	char	*path;

	path = NULL;
	*fk = fork();
	if (*fk == -1)
		return ;
	if (*fk == 0)
	{
		printf("\n\tChild:\n");
		printf("\t\tpip[0]: [%d]\n", pip[0]);
		printf("\t\tpip[1]: [%d]\n", pip[1]);
		path = get_path(cmd->meta.exec_cmd[0], shell->env);
		if (path != NULL)
		{
			execve(path, cmd->meta.exec_cmd, shell-> envi);
			perror("minishell");
			exit_forkfailure(EXIT_FAILURE, shell, pip, &path);
		}
		exit_forkfailure(127, shell, pip, &path);
	}
}

void	redirection(int fd, int todup)
{
	if (fd > 2 && todup > 2)
		dup2(fd, todup);
}

int	select_dup(int *pip, int old_pipr, t_cmd *cmd)
{
	if (cmd)
	{
		s_close(pip[0]);
		redirection(old_pipr, STDIN_FILENO);
		redirection(pip[1], STDOUT_FILENO);
		// redirection(cmd->meta.infile, STDIN_FILENO);
		// redirection(cmd->meta.outfile, STDOUT_FILENO);
		return (1);
	}
	return (0);
}

void	launch_command(t_linux *shell, t_cmd *command)
{
	pid_t	fork_id;
	int		old_pipr;
	int		pip[2];

	/*DEBUG*/	db_printf("\nLaunch Command\n\n\n", FE_UND);
	fork_id = 0;
	old_pipr = -1;
	pip[0] = -1;
	pip[1] = -1;
	let_signal_through();
	command = shell->head->next;
	while (command && command->meta.exec_cmd)
	{
		if (pipe(pip) == -1)
			break ;
		select_dup(pip, old_pipr, command);
		if (!is_builtin(command->meta.exec_cmd[0], shell))
		{
			if (command->meta.exec_cmd)
				exe_command(command, &fork_id, pip, shell);
			waitpid(fork_id, &g_sign, 0);
		}
		s_close(pip[0]);
		dup2(old_pipr, pip[1]);
		command = command->next;
	}
	s_close(old_pipr);
	change_ret_signal(g_sign);
	create_signal();
	/*DEBUG*/	db_printf("\n\nCOMMANDS ALL DONE\n\n", FE_BOL);
}
