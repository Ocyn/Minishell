/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocyn <ocyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/10 21:52:29 by ocyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	annihiliation(t_linux *shell, int *pip)
{
	(void)pip;
	close(pip[1]);
	close(pip[0]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	s_free(&shell->input);
	s_free(&shell->prompt);
	free_tab(shell->token, tablen(shell->token));
	cmd_free_list(shell->head);
	free(shell->head);
}

void	exe_command(t_cmd *cmd, pid_t *fk, int *pip, t_linux *shell)
{
	char	*path;

	path = NULL;
	(void)shell;
	(void)pip;
	printf("\n%sExecution :%s", FE_UND, FRR);
	*fk = fork();
	if (*fk == -1)
		return ;
	if (*fk == 0)
	{
		path = get_path(cmd->command.prefixes[0], cmd->command.env_var);
		printf("execve(%s, ", path);
		db_tabstr_display(cmd->command.prefixes, "args", -1);
		printf(", Env[Too long])\n");
		printf("%s", BND_DARK_GRAY);
		execve(path, cmd->command.prefixes, cmd->command.env_var);
		perror("bash");
		annihiliation(shell, pip);
		s_free(&path);
		exit (0);
	}
	printf("%s", FRR);
}

void	redirection(int pip, int pipnext, int fdclose)
{
	printf("\n%sRedirection :%s", FE_UND, FRR);
	printf("\n\tClosing %d", fdclose);
	printf("\n\tDup2 %d -> %d", pipnext, pip);
	printf("\n\tClosing %d\n\n", pip);
	close(fdclose);
	dup2(pipnext, pip);
	// close(pip);
}

int	select_dup(int *pip, t_cmd *command)
{
	if (command->prev && command->command.args \
	&& command->prev->type == INFILE_CMD)
		redirection(set_infile(command->command.args[0]), STDIN_FILENO, pip[0]);
	if (command->next && command->command.args \
	&& command->next->type == OUTFILE_CMD)
		redirection(set_outfile(command->command.args[0]), STDOUT_FILENO, pip[1]);
	if (command && command->type == PIPE_CMD)
		redirection(pip[1], STDOUT_FILENO, pip[0]);
	if (command->prev && command->prev->type == PIPE_CMD)
		redirection(pip[0], STDIN_FILENO, pip[1]);
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

	fork_id = 0;
	ft_memset(pipfd, 0, 2);
	pipe(pipfd);
	if (!pipfd[0] || !pipfd[1])
		return ;
	command = shell->head->next;
	while (command)
	{
		create_signal(nothing, nothing);
		command->command.env_var = shell->envi;
		if (select_dup(pipfd, command))
		{
			exe_command(command, &fork_id, pipfd, shell);
			fork_id = 0;
		}
		command = command->next;
		create_signal(ctrl_c, ctrl_slash);
	}
	close(pipfd[1]);
	close(pipfd[0]);
	waitpid(fork_id - 1, 0, 0);
	waitpid(fork_id, 0, 0);
}
