/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/21 23:05:37 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exe_command(char **command, pid_t *fk, int *pip, t_linux *shell)
{
	char	*path;

	path = NULL;
	*fk = fork();
	if (*fk == -1)
		return ((void)err_perror(1));
	if (*fk == 0)
	{
		path = get_path(command[0], shell->env);
		if (path != NULL)
		{
			execve(path, command, shell->envi);
			exit_forkfailure(EXIT_FAILURE, shell, pip, &path);
		}
		exit_forkfailure(127, shell, pip, &path);
	}
}

int	pipe_tool(int *piipe, int initorclose)
{
	if (initorclose)
	{
		ft_memset(piipe, -1, 2);
		if (pipe(piipe) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (close(piipe[0]) == -1 || close(piipe[1]) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	select_dup(int *pi_in, int *pi_out, t_cmd *cmd)
{
	(void)pi_out;
	(void)pi_inz;
	if (cmd)
	{
		/*DEBUG*/	printf("\n\tSelect dup:\n");
		/*DEBUG*/	printf("\t\tpi_in[0][1]: [%d] [%d]\n", pi_in[0], pi_in[1]);
		/*DEBUG*/	printf("\t\tpi_out[0][1]: [%d] [%d]\n", pi_out[0], pi_out[1]);
		dup2(cmd->meta.infile, STDIN_FILENO);
		dup2(cmd->meta.outfile, STDOUT_FILENO);
		return (1);
	}
	return (0);
}

void	launch_command(t_linux *shell, t_cmd *command)
{
	pid_t	fork_id;
	int		pi_in[2];
	int		pi_out[2];

	/*DEBUG*/	db_printf("\nLaunch Command\n\n\n", FE_UND);
	fork_id = 0;
	err_perror((pipe_tool(pi_in, 1) || pipe_tool(pi_out, 1)));
	let_signal_through();
	command = shell->head->next;
	while (command && command->meta.exec_cmd)
	{
		select_dup(pi_in, pi_out, command);
		if (!is_builtin(command->meta.exec_cmd[0], shell))
		{
			/*DEBUG*/	db_printf("\n\nOUTPUT START\n\n", FE_BOL);
			exe_command(command->meta.exec_cmd, &fork_id, pi_in, shell);
			/*DEBUG*/	db_printf("\n\nOUTPUT END\n\n", FE_BOL);
			waitpid(fork_id, &g_sign, 0);
		}
		command = command->next;
	}
	err_perror((pipe_tool(pi_in, 0) || pipe_tool(pi_out, 0)));
	change_ret_signal(g_sign);
	create_signal();
}
