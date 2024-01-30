/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/30 16:13:39 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	exe_command(t_cmd *cmd, pid_t *fk, int *pip, t_linux *shell)
{
	char	*path;

	path = NULL;
	(void)pip;
	(void)shell;
	*fk = fork();
	if (*fk == -1)
		return ;
	if (*fk == 0)
	{
		printf("%s%d Execution Of %s%s :%s\n", FE_UND, cmd->id, FE_BOL, cmd->command.prefixes[0], FRR);
		path = get_path(cmd->command.prefixes[0], cmd->command.env_var);
		db_tabstr_display(cmd->command.prefixes, "args", -1);
		printf(", Env[Too long])\n\n");
		printf("%s", BND_DARK_GRAY);
		execve(path, cmd->command.prefixes, cmd->command.env_var);
		perror("bash");
		exit_forkfailure(1, shell, pip);
		s_free(&path);
		exit (EXIT_FAILURE);
	}
	printf ("%s", FRR);
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
		redirection(command->infile.fd, STDERR_FILENO);
		redirection(command->outfile.fd, STDOUT_FILENO);
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
		pipe(pip);
		if (!pip[0] || !pip[1])
			return ;
		command->command.env_var = shell->envi;
		select_dup(pip, command);
		if (!is_builtin(command->command.prefixes[0], shell))
			exe_command(command, &fork_id, pip, shell);
		close(pip[1]);
		close(pip[0]);
		waitpid(fork_id, &g_sign, 0);
		command = command->next;
	}
	create_signal();
}
