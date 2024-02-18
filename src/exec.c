/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/18 23:50:38 by jcuzin           ###   ########.fr       */
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
		path = get_path(cmd->meta.raw[0], shell->env);
		if (path != NULL)
		{
			execve(path, cmd->meta.raw, shell->envi);
			perror("bash");
			exit_forkfailure(EXIT_FAILURE, shell, pip, &path);
		}
		exit_forkfailure(127, shell, pip, &path);
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

void	launch_command(t_linux *shell, t_cmd *command)
{
	pid_t	fork_id;
	int		pip[2];

	fork_id = 0;
	let_signal_through();
	ft_memset(pip, 0, 2);
	command = shell->head->next;
	while (command)
	{
		if (!is_builtin(command->meta.raw[0], shell))
		{
			if (pipe(pip) || !pip[0] || !pip[1])
				break ;
			select_dup(pip, command);
			if (command->meta.raw[0])
				exe_command(command, &fork_id, pip, shell);
			close(pip[1]);
			close(pip[0]);
			waitpid(fork_id, &g_sign, 0);
		}
		command = command->next;
	}
	waitpid(fork_id, &g_sign, 0);
	change_ret_signal(g_sign);
	create_signal();
}
