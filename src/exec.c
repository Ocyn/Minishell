/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/21 14:21:20 by jcuzin           ###   ########.fr       */
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
		path = get_path(cmd->meta.exec_cmd[0], shell->env);
		if (path != NULL)
		{
			execve(path, cmd->meta.exec_cmd, shell->envi);
			perror("minishell");
			exit_forkfailure(EXIT_FAILURE, shell, pip, &path);
		}
		exit_forkfailure(127, shell, pip, &path);
	}
}

void	redirection(int fd, int todup, int toclose)
{
	if (fd > 2 && todup > 2)
	{
		dup2(fd, todup);
		if (toclose > 2)
			s_close(toclose);
	}
}

int	select_dup(int *pip, t_cmd *cmd)
{
	if (cmd && pip)
	{
		if (cmd->meta.infile > 2)
			redirection(cmd->meta.infile, STDIN_FILENO, 0);
		if (pip[0] != -1)
			redirection(pip[0], STDIN_FILENO, pip[1]);
		if (cmd->meta.outfile > 2)
			redirection(cmd->meta.outfile, STDOUT_FILENO, 0);
		if (cmd->next && pip[1] != -1)
			redirection(pip[1], STDOUT_FILENO, pip[0]);
		return (1);
	}
	return (0);
}

void	launch_command(t_linux *shell, t_cmd *command)
{
	pid_t	fork_id;
	int		pip[2];

	/*DEBUG*/	db_printf("\nLaunch Command\n\n\n", FE_UND);
	fork_id = 0;
	ft_memset(pip, 0, 2);
	let_signal_through();
	command = shell->head->next;
	while (command && command->meta.exec_cmd)
	{
		if (!is_builtin(command->meta.exec_cmd[0], shell))
		{
			if (pipe(pip) == -1 || !pip[0] || !pip[1])
				break ;
			select_dup(pip, command);
			if (command->meta.exec_cmd[0])
				exe_command(command, &fork_id, pip, shell);
			s_close(pip[1]);
			s_close(pip[0]);
			waitpid(fork_id, &g_sign, 0);
		}
		command = command->next;
	}
	waitpid(fork_id, &g_sign, 0);
	change_ret_signal(g_sign);
	create_signal();
	/*DEBUG*/	db_printf("\n\nCOMMANDS ALL DONE\n\n", FE_BOL);
}
