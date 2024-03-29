/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 08:14:08 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/23 07:21:24 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	s_close(int launch, int fd)
{
	if (launch && fd != -1)
		return (close(fd));
	return (0);
}

void	change_var_sign(char **str)
{
	char	*buf;

	buf = ft_itoa(g_sign);
	if (!buf)
		return ;
	str_edit(str, "$?", buf);
	s_free(&buf);
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
