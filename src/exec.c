/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 11:27:03 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_command(char **command, char **v_env, pid_t *f_id, int *ipipe)
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
		close(ipipe[0]);
		execve(path, command, v_env);
		perror("bash");
	}
	close(ipipe[1]);
}

char	**singlecmd(char  )

void	exec_all(t_linux *shell)
{
	pid_t	f_id;
	int		ipipe[2];
	int		i;

	i = 0;
	pipe(ipipe);
	if (shell->exe.infile)
	{
		dup2(shell->exe.infile, STDIN_FILENO);
		dup2(ipipe[1], STDOUT_FILENO);
		i += 2;
	}
	while (shell->exe.f_cmd[i] && shell->exe.pipe_nb > 0)
	{
		dup2(ipipe[0], STDIN_FILENO);
		dup2(ipipe[1], STDOUT_FILENO);
		
		execute_command(shell->exe.f_cmd + i, shell->envi, &f_id, ipipe);
		shell->exe.pipe_nb--;
		i++;
	}
	if (shell->exe.outfile)
		dup2(shell->exe.outfile, STDOUT_FILENO);
	execute_command(shell->exe.f_cmd + i, shell->envi, &f_id, ipipe);
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
	i = 0;
	check = ft_strjoin("/", command);
	while (var[i])
	{
		cmd_path = ft_strjoin(var[i], check);
		if (!access(cmd_path, F_OK))
			break ;
		s_free(&cmd_path);
		i++;
	}
	free_tab(var, tablen(var));
	return (s_free(&check), cmd_path);
}
