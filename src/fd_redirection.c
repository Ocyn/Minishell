/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:14:41 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/16 17:57:42 by jcuzin           ###   ########.fr       */
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

int	set_infile(char *file, int *fd, int heredoc)
{
	(void)heredoc;
	if (!file)
		return (EXIT_FAILURE);
	/*DEBUG*/	printf("\n\t\tinfile to open : [%s]\n", file);
	if (!access(file, F_OK) && !access(file, R_OK))
		*fd = open(file, O_RDONLY);
	if (!*fd)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_outfile(char *file, int *fd, int overwrite)
{
	if (!file)
		return (EXIT_FAILURE);
	/*DEBUG*/	printf("\n\t\toutfile to open : [%s]\n", file);
	if (overwrite)
		*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00700);
	else
		*fd = open(file, O_CREAT | O_WRONLY, 00700);
	if (!*fd || !access(file, F_OK) || !access(file, W_OK))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
