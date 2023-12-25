/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 14:57:11 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_command(char **command, char **v_env, pid_t *f_id, int *fd_dup)
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
		close(fd_dup[1]);
		dup2(fd_dup[0], STDIN_FILENO);
		printf("\tEXE [%s][%s\'  \'%s][%s]\n", path, command[0], command[1], v_env[0]);
		execve(path, command, v_env);
		perror("bash");
		free_tab(command, tablen(command));
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		close(fd_dup[0]);
		close(fd_dup[1]);
		exit (0);
	}
	close(fd_dup[0]);
	close(fd_dup[1]);
}

void	exec_all(t_linux *shell)
{
	pid_t	f_id;
	int		fd_dup[2];
	int		ipipe[2];
	int		i;

	i = 0;
	pipe(ipipe);
	fd_dup[0] = ipipe[0];
	fd_dup[1] = ipipe[1];
	if (shell->exe.infile)
	{
		fd_dup[0] = shell->exe.infile;
		i += 2;
	}
	while (shell->exe.f_cmd[i] && shell->exe.pipe_nb > 0)
	{
		while (shell->exe.f_cmd[i] && shell->exe.f_cmd[i][0] != '|')
			i++;
		if (shell->exe.f_cmd[i] && shell->exe.f_cmd[i][0] == '|')
			i++;
		execute_command(shell->exe.f_cmd + i, shell->envi, &f_id, fd_dup);
		shell->exe.pipe_nb--;
		fd_dup[0] = ipipe[0];
		fd_dup[1] = ipipe[1];
	}
	if (shell->exe.outfile)
		fd_dup[1] = shell->exe.outfile;
	execute_command(shell->exe.f_cmd + i, shell->envi, &f_id, fd_dup);
	close(ipipe[1]);
	close(ipipe[0]);
	waitpid(f_id - 1, 0, 0);
	waitpid(f_id, 0, 0);
}


char	*get_path(char *command, char **env)
{
	char	*cmd_path;
	char	*check;
	char	**var;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp(env[i], "PATH=", 5) != 0)
		return (NULL);
	cmd_path = ft_strtrim(env[i], "PATH=");
	var = ft_split(cmd_path, ':');
	s_free(&cmd_path);
	i = -1;
	check = ft_strjoin("/", command);
	while (var[++i])
	{
		cmd_path = ft_strjoin(var[i], check);
		if (!access(cmd_path, F_OK))
			break ;
		s_free(&cmd_path);
	}
	if (!cmd_path)
		cmd_path = command;
	return (free_tab(var, tablen(var)), s_free(&check), cmd_path);
}
