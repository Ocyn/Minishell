/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_edit_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:03:20 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/22 20:01:57 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*str_quote_edit_init(char *src, char *seek, char *replace, int *llen);

int	str_edit_quotes(char **src, char *seek, char *replace, int i)
{
	char	*new;
	char	*str;
	int		len;
	int		j;
	int		ret;

	len = ft_strlen(*src);
	str = *src;
	j = -1;
	ret = 0;
	new = str_quote_edit_init(&str[i], seek, replace, &len);
	while (++j < i)
		new[j] = str[j];
	if (str_occur(str + i, seek))
	{
		j += ft_strcat(new + i, replace);
		str += ft_strlen(seek) - ft_strlen(replace);
		ret = ft_strlen(replace) - ft_strlen(seek);
	}
	j--;
	while (++j < len)
		new[j] = str[j];
	free(*src);
	*src = new;
	return (ret);
}

char	*str_quote_edit_init(char *src, char *seek, char *replace, int *llen)
{
	char	*new;
	int		len;

	len = 0;
	new = NULL;
	if (str_occur(src, seek))
		len++;
	len = *llen + (len * (ft_strlen(replace) - ft_strlen(seek)));
	new = s_malloc(sizeof(char) * (len + 1));
	*llen = len;
	return (new);
}
