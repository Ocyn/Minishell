/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/09 03:30:50 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	change_ret_signal(int c)
{
	if (WIFEXITED(c))
		g_sign = WEXITSTATUS(c);
	else if (WIFSIGNALED(c))
	{
		if (WTERMSIG(c) == SIGQUIT)
			g_sign = 131;
		if (WTERMSIG(c) == SIGINT)
			g_sign = 130;
	}
}

void	exe_command(t_cmd *cmd, pid_t *fk, int *pip, t_linux *shell)
{
	char	*path;

	path = NULL;
	*fk = fork();
	if (*fk == -1)
		return ;
	if (*fk == 0)
	{
		path = get_path(cmd->meta.exec_cmd[0], shell->envi);
		execve(path, cmd->meta.exec_cmd, shell->envi);
		perror("bash");
		exit_forkfailure(1, shell, pip, &path);
	}
}

void	redirection(int fd, int todup)
{
	if (fd)
		dup2(fd, todup);
	else
		close(fd);
}

int	select_dup(int *pip, t_cmd *command)
{
	if (!pip)
	{
		redirection(command->meta.infile, STDERR_FILENO);
		redirection(command->meta.outfile, STDOUT_FILENO);
	}
	return (1);
}

void	launch_command(t_linux *shell)
{
	t_cmd	*command;
	pid_t	fork_id;
	int		pip[2];

	fork_id = 0;
	let_signal_cook();
	ft_memset(pip, 0, 2);
	command = shell->head->next;
	while (command)
	{
		if (pipe(pip) || !pip[0] || !pip[1])
			break ;
		select_dup(pip, command);
		if (command->meta.exec_cmd \
		&& !is_builtin(command->meta.exec_cmd[0], shell))
			exe_command(command, &fork_id, pip, shell);
		close(pip[1]);
		close(pip[0]);
		if (waitpid(fork_id, &g_sign, 0) == -1)
			break ;
		change_ret_signal(g_sign);
		command = command->next;
	}
	create_signal();
}
