/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/07 20:47:57 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exe_command(t_cmd *cmd, pid_t *fk)
{
	char	*path;

	path = NULL;
	*fk = fork();
	if (*fk == -1)
		return ;
	if (*fk == 0)
	{
		db_print_custom_font("\nExecution\n", FE_UND);
		path = get_path(cmd->command.prefixes[0], cmd->command.env_var);
		printf("execve(%s, ", path);
		db_tabstr_display(cmd->command.prefixes, "args", -1);
		printf(", Env[Too long])\n");
		execve(path, cmd->command.prefixes, cmd->command.env_var);
		perror("bash");
		s_free(&path);
	}
}

void	redirection(int pip, int pipnext)
{
	dup2(pipnext, pip);
	close(pip);
}

int	select_dup(int *pip, int *pipnext, t_cmd *command)
{
	if (command->prev && command->prev->type == INFILE_CMD)
		redirection(set_infile(command->command.args[0]), STDIN_FILENO);
	if (command->next && command->next->type == OUTFILE_CMD)
		redirection(set_outfile(command->command.args[0]), STDOUT_FILENO);
	if (command && command->type == PIPE_CMD)
		redirection(pipnext[0], pip[1]);
	if (command->prev && command->prev->type == PIPE_CMD)
		redirection(pip[0], pipnext[1]);
	if (command && (command->type == INFILE_CMD || command->type == OUTFILE_CMD \
	|| command->type == OUTFILE_ADDER))
		return (0);
	return (1);
}

void	launch_command(t_linux *shell)
{
	t_cmd	*command;
	pid_t	fork_id;
	int		pipfd[2];
	int		pipfd_next[2];

	fork_id = 0;
	ft_memset(pipfd, 0, 2);
	ft_memset(pipfd_next, 0, 2);
	pipe(pipfd);
	pipe(pipfd_next);
	if (!pipfd[0] || !pipfd[1] || !pipfd_next[0] || !pipfd_next[1])
		return ;
	command = shell->head->next;
	while (command)
	{
		command->command.env_var = shell->envi;
		if (select_dup(pipfd, pipfd_next, command))
			exe_command(command, &fork_id);
		command = command->next;
	}
	if (close(pipfd[0] == -1 || close(pipfd[1] == -1)))
		printf("\nCLOSING FAILED\n");
	if (close(pipfd_next[0] == -1 || close(pipfd_next[1] == -1)))
		printf("\nCLOSING FAILED\n");
	waitpid(fork_id, 0, 0);
	waitpid(fork_id - 1, 0, 0);
}
