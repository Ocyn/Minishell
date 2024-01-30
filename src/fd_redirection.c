/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:14:41 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/30 21:14:55 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

int	set_outfile(char *file, int overwrite)
{
	int	fd;

	fd = 0;
	if (!file)
		return (0);
	if (overwrite)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00700);
	else
		fd = open(file, O_CREAT | O_WRONLY, 00700);
	if (!fd || !access(file, F_OK) || !access(file, W_OK))
		return (0);
	return (fd);
}
