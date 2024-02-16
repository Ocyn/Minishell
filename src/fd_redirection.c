/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:14:41 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/14 12:47:29 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_file_name(char *token, char type)
{
	char	*name;
	int		len;

	len = 0;
	if (!token || !token[0])
		return (NULL);
	name = ft_strrchr(token, type);
	while (name && name[0] && name[0] == ' ')
		name++;
	while (name && name[len] && name[len] != ' ')
		len++;
	if (!name)
		return (NULL);
	printf("\n\t\t\tFT REDI: [%s]\n", name);
	return (name);
}

int	set_infile(char *file, int heredoc)
{
	int		fd;

	fd = 0;
	(void)heredoc;
	printf("\n\t\tfile to open : [%s]\n", file);
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
