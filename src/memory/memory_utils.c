/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 08:14:08 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/22 13:43:12 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	s_close(int fd)
{
	if (fd != -1)
		return (close(fd));
	return (0);
}

char	**tab_dup(char **token_tab, int token_len)
{
	char	**raw;
	int		i;

	i = -1;
	raw = NULL;
	raw = s_malloc(sizeof(char *) * (token_len + 1));
	while (++i < token_len)
		raw[i] = ft_strdup(token_tab[i]);
	return (raw);
}

char	*ft_strtok(char *src, char delim)
{
	int	id;

	id = 0;
	if (src && delim)
	{
		src = ft_strchr(src, delim);
		src += (src && src[0] && src[1]);
		while (src && src[id] && src[id] != delim)
			id++;
		src[id] = 0;
	}
	return (src);
}
