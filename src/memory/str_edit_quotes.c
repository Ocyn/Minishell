/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_edit_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:03:20 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/20 21:56:36 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*str_edit_init(char **src, char *seek, char *replace, int *llen);

void	str_edit_quotes(char **src, char *seek, char *replace)
{
	char	*new;
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	str = *src;
	new = str_edit_init(src, seek, replace, &len);
	while (i < len)
	{
		if (str_occur(str + i, seek))
		{
			i += ft_strcat(new, replace);
			str += ft_strlen(seek) - ft_strlen(replace);
		}
		else
		{
			new[i] = str[i];
			i++;
		}
	}
	free(*src);
	*src = new;
}

static char	*str_edit_init(char **src, char *seek, char *replace, int *llen)
{
	char	*new;
	char	*str;
	int		len;
	int		i;

	i = -1;
	len = 0;
	str = *src;
	new = NULL;
	while (str && str[++i])
		if (str_occur(str + i, seek))
			len++;
	i = 0;
	len = ft_strlen(*src) + (len * (ft_strlen(replace) - ft_strlen(seek)));
	new = s_malloc(sizeof(char) * (len + 1));
	*llen = len;
	return (new);
}
