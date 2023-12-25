/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 07:59:22 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/25 14:38:16 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		chkconfig(char **check, char *config);
int		set_infile(char *file, t_linux *shell);
int		set_outfile(char *file, t_linux *shell);

int	set_command(t_linux *shell)
{
	char	**command;
	int		i;
	int		err;

	i = 0;
	err = 0;
	shell->exe.infile = 0;
	shell->exe.outfile = 0;
	if (shell->exe.arg_n < 3)
		return (1);
	command = shell->exe.f_cmd;
	if (!ft_strcmp(command[0], "<"))
		err = set_infile(command[1], shell);
	if (!ft_strcmp(command[shell->exe.arg_n - 2], ">"))
		err = set_outfile(command[shell->exe.arg_n - 1], shell);
	while (command[i])
	{
		if (!ft_strcmp(command[i], "|"))
			shell->exe.pipe_nb++;
		i++;
	}
	printf("\tpipes: %d\t", shell->exe.pipe_nb);
	return (1);
}

int	set_infile(char *file, t_linux *shell)
{
	if (!file || shell->exe.infile != 0)
		return (0);
	if (!access(file, F_OK) && !access(file, R_OK))
		shell->exe.infile = open(file, O_RDONLY);
	if (!shell->exe.infile)
		return (0);
	return (1);
}

int	set_outfile(char *file, t_linux *shell)
{
	if (!file || shell->exe.outfile != 0)
		return (0);
	if (!access(file, F_OK) && access(file, W_OK))
		return (0);
	shell->exe.outfile = open(file, O_CREAT | O_RDWR, 00700);
	if (!shell->exe.outfile)
		return (0);
	return (1);
}
