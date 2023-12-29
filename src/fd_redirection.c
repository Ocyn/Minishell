/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 07:59:22 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/29 11:28:59 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*fd_redirection(char *file, t_cmd *command)
{
	if (!file || !command)
		return (command);
	if (command->type == '<')
		command->infile = set_infile(file);
	if (command->type == '>')
		command->outfile = set_outfile(file);
	return (command);
}

int	set_infile(char *file)
{
	int	fd;

	fd = 0;
	if (!file)
		return (0);
	if (!access(file, F_OK) && !access(file, R_OK))
		fd = open(file, O_RDONLY);
	if (!fd)
		return (0);
	return (fd);
}

int	set_outfile(char *file)
{
	int	fd;

	fd = 0;
	if (!file)
		return (0);
	if (!access(file, F_OK) && access(file, W_OK))
		return (0);
	fd = open(file, O_CREAT | O_RDWR, 00700);
	if (!fd)
		return (0);
	return (fd);
}
