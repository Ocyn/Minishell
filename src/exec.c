/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocyn <ocyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/11 06:52:25 by ocyn             ###   ########.fr       */
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
	if (cmd->type == INFILE_CMD || cmd->type == OUTFILE_ADDER || cmd->type == OUTFILE_CMD)
		return ;
	*fk = fork();
	if (*fk == -1)
		return ;
	if (*fk == 0)
	{
		printf("%s%d Execution Of %s%s :%s\n", FE_UND, cmd->id, FE_BOL, cmd->command.prefixes[0] ,FRR);
		path = get_path(cmd->command.prefixes[0], cmd->command.env_var);
		printf("execve(%s, ", path);
		db_tabstr_display(cmd->command.prefixes, "args", -1);
		printf(", Env[Too long])\n\n");
		printf("%s", BND_DARK_GRAY);
		execve(path, cmd->command.prefixes, cmd->command.env_var);
		perror("bash");
		annihiliation(shell, pip);
		s_free(&path);
		exit (0);
	}
	printf("%s", FRR);
}

void	redirection(int fdin, int fdout, int toclose)
{
	if (toclose)
		close(toclose);
	printf("\n%sRedirection :%s", FE_UND, FRR);
	printf("\n\tDup2 %d -> %d", fdin, fdout);
	if (fdin)
		dup2(fdin, STDIN_FILENO);
	printf("\n\tDup2 %d -> %d", fdin, fdout);
	if (fdout)
		dup2(fdout, STDOUT_FILENO);
}

int	select_dup(int *pip, t_cmd *command)
{
	if (command->prev && command->prev->command.args \
	&& command->prev->type == INFILE_CMD)
		redirection(set_infile(command->prev->command.args[0]), 0, 0);
	if (command->next && command->next->command.args \
	&& command->next->type == OUTFILE_CMD)
		redirection(0, set_outfile(command->next->command.args[0], 1), 0);
	if (command->prev && command->prev->type == PIPE_CMD)
		redirection(pip[0], pip[1], STDIN_FILENO);
	if (command && command->type == PIPE_CMD)
		redirection(pip[1], STDOUT_FILENO, pip[0]);
	if (!command->next)
		return (0);
	return (1);
}

void	launch_command(t_linux *shell)
{
	t_cmd	*command;
	pid_t	fork_id;
	int		pip[2];

	fork_id = 0;
	ft_memset(pip, 0, 2);
	pipe(pip);
	if (!pip[0] || !pip[1])
		return ;
	command = shell->head->next;
	while (command)
	{
		create_signal(nothing, nothing);
		command->command.env_var = shell->envi;
		select_dup(pip, command);
		exe_command(command, &fork_id, pip, shell);
		command = command->next;
		create_signal(ctrl_c, ctrl_slash);
	}
	close(pip[1]);
	close(pip[0]);
	waitpid(fork_id - 1, 0, 0);
	waitpid(fork_id, 0, 0);
}
