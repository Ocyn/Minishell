/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 07:59:22 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/29 13:10:39 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*fd_redirection(t_cmd *command, char **token)
{
	if (!command)
		return (command);
	if (command->type == '<')
		command->infile = set_infile(token[command->id]);
	if (command->type == '>')
		command->outfile = set_outfile(token[command->id + 1]);
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
