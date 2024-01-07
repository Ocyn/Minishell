/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 07:59:22 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 20:31:05 by jcuzin           ###   ########.fr       */
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
