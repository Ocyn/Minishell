/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:14:41 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/09 12:12:33 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_file_name(char *token)
{
	char	*name;
	int		len;

	len = 0;
	name = NULL;
	if (token)
	{
		name = token;
		while (token[0] && token[0] == ' ')
			token++;
		if (!token || !token[0])
			return (NULL);
		while (token[len] && token[len] != ' ')
			len++;
		name[len] = 0;
		//name = ft_substr(token, 0, len);
		if (!name)
			return (NULL);
	}
	return (name);
}

int	set_infile(char *file, int heredoc)
{
	int		fd;


	fd = 0;
	(void)heredoc;
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
