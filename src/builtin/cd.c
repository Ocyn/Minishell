/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:08:13 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 00:42:20 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*cut_cmd(char *str)
{
	char	*path;
	int		i;
	int		j;

	i = 2;
	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i + j])
		j++;
	if (j > 0)
	{
		path = malloc(sizeof(char) * j + 1);
		if (!path)
			return (NULL);
		j = 0;
		while (str[i + j])
		{
			path[j] = str[i + j];
			j++;
		}
		path[j] = '\0';
		return (path);
	}
	return ("cd");
}

void	ft_cd(char *cmd)
{
	char	*path;
	char	home[1];

	home[0] = '~';
	path = cut_cmd(cmd);
	if (path)
	{
		if (!ft_strcmp(cmd, path))
		{
			printf ("il faut aller dans le repertoire ~\n");
		}
		else
		{
			if (chdir(path) != 0)
			{
				perror("chdir");
				free (path);
			}
		}
			//il faut aussi gerer le cas du ~
			//et le cas ou on est dans un repertoire qui n'existe plus
	}
}
