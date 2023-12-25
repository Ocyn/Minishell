/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 16:32:06 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_command(char **command, char **v_env, pid_t *f_id)
{
	char	*path;

	path = NULL;
	*f_id = fork();
	if (*f_id == -1)
		return (perror("fork"));
	if (*f_id == 0)
	{
		if (!access(command[0], F_OK))
			path = command[0];
		else
			path = get_path(command[0], v_env);
		printf("\tEXE [%s][%s\'  \'%s][%s]\n", path, command[0], command[1], v_env[0]);
		execve(path, command, v_env);
		perror("bash");
		free_tab(command, tablen(command));
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		exit (0);
	}
}

void	execute_command_rout(char **command, t_linux *shell, pid_t *f_id, int *ipipe)
{
	char	*path;

	path = NULL;
	*f_id = fork();
	if (*f_id == -1)
		return (perror("fork"));
	if (*f_id == 0)
	{
		if (!access(command[0], F_OK))
			path = command[0];
		else
			path = get_path(command[0], shell->envi);
		close(ipipe[1]);
		s_free(&command[1]);
		if (shell->exe.pipe_nb > 0)
			dup2(ipipe[0], STDIN_FILENO);
		dup2(shell->exe.outfile, STDOUT_FILENO);
		printf("\tEXE [%s][%s\'  \'%s][%s]\n", path, command[0], command[1], shell->envi[0]);
		execve(path, command, shell->envi);
		perror("bash");
		free_tab(command, tablen(command));
		close(ipipe[0]);
		close(shell->exe.outfile);
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		exit (0);
	}
}

void	execute_command_rin(char **command, t_linux *shell, pid_t *f_id, int *ipipe)
{
	char	*path;

	path = NULL;
	*f_id = fork();
	if (*f_id == -1)
		return (perror("fork"));
	if (*f_id == 0)
	{
		if (!access(command[0], F_OK))
			path = command[0];
		else
			path = get_path(command[0], shell->envi);
		close(ipipe[0]);
		dup2(shell->exe.infile, STDIN_FILENO);
		if (shell->exe.pipe_nb > 0)
			dup2(ipipe[1], STDOUT_FILENO);
		printf("\tEXE [%s][%s\'  \'%s][%s]\n", path, command[0], command[1], shell->envi[0]);
		execve(path, command, shell->envi);
		perror("bash");
		free_tab(command, tablen(command));
		close(ipipe[1]);
		close(shell->exe.infile);
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		exit (0);
	}
}

void	exec_all(t_linux *shell)
{
	pid_t	f_id;
	int		ipipe[2];
	int		i;

	i = 0;
	f_id = 0;
	pipe(ipipe);
	if (shell->exe.infile)
	{
		execute_command_rin(shell->exe.f_cmd + 2, shell, &f_id, ipipe);
		i += 2;
	}
	while (shell->exe.f_cmd[i] && shell->exe.pipe_nb > 0)
	{
		while (shell->exe.f_cmd[i] && shell->exe.f_cmd[i][0] != '|')
			i++;
		while (shell->exe.f_cmd[i] && shell->exe.f_cmd[i][0] == '|')
			i++;
		close(ipipe[i % 2]);
		dup2(ipipe[i + 1 % 2], STDIN_FILENO);
		execute_command(shell->exe.f_cmd + i, shell->envi, &f_id);
		close(ipipe[i % 2]);
		shell->exe.pipe_nb--;
	}
	if (shell->exe.outfile)
		execute_command_rout(shell->exe.f_cmd + i, shell, &f_id, ipipe);
	if (!shell->exe.infile && !shell->exe.outfile && i == 0)
		execute_command(shell->exe.f_cmd, shell->envi, &f_id);
	close(ipipe[1]);
	close(ipipe[0]);
	waitpid(f_id - 1, 0, 0);
	waitpid(f_id, 0, 0);
}
