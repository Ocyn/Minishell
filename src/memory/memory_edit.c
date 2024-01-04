/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:03:20 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/04 09:00:37 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*str_edit_init(char **src, char *seek, char *replace, int *llen);

int	str_occur(const char *src, const char *seek)
{
	int	i;
	int	len_src;
	int	len_seek;

	i = 0;
	if (!src || !seek)
		return (0);
	len_src = (int)ft_strlen(src);
	len_seek = (int)ft_strlen(seek);
	while (i < len_src && i < len_seek && src[i] && src[i] == seek[i])
		i++;
	if (i == len_seek)
		return (1);
	return (0);
}

void	str_edit(char **src, char *seek, char *replace)
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

char	*str_edit_init(char **src, char *seek, char *replace, int *llen)
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

int	ft_strcat(char *dest, char *src)
{
	int		i;
	int		len;

	i = 0;
	len = (int)ft_strlen((char *)dest);
	while (src[i])
	{
		dest[i + len] = src[i];
		i++;
	}
	dest[i + len] = 0;
	return (i);
}

void	insert_tab_in_tab(char **insert, char ***tab, int where)
{
	char	**new;
	int		ins_;
	int		i;
	int		len;

	i = -1;
	ins_ = 0;
	new = NULL;
	len = tablen(*tab) + tablen(insert);
	if (!insert || !len || tablen(*tab) < where)
		return ;
	new = s_malloc(sizeof(char *) * (len + 1));
	if (!new)
		return ;
	while (++i < len && i - ins_ >= 0 && (*tab)[i - ins_])
	{
		db_tabstr_display(*tab, "\n\tCopy Tab ", i - ins_);
		if (i == where - 1)
			while (insert[ins_])
				new[i++] = ft_strdup(insert[ins_++]);
		if (i - ins_ == where - 1)
			ins_ -= (ins_ <= i);
		new[i] = ft_strdup((*tab)[i - ins_]);
	}
	free_tab(*tab, tablen(*tab));
	*tab = new;
}
