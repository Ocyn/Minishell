/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_scan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:49:05 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 06:38:53 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	find_str_in_tab(int strict_mode, char *find, char **tab)
{
	int	i;

	i = -1;
	if (!find || !tab)
		return (0);
	while (find && tab && tab[++i])
	{
		if (find_str_in_str(tab[i], find))
			if (!strict_mode || (strict_mode && !ft_strcmp(tab[i], find)))
				return (i);
	}
	return (0);
}

int	find_str_in_str(const char *src, const char *seek)
{
	int	i;
	int	find;
	int	len_src;
	int	len_seek;

	i = -1;
	if (!src || !seek)
		return (0);
	len_src = (int)ft_strlen(src);
	len_seek = (int)ft_strlen(seek);
	while (++i < len_src && src[i])
	{
		find = -1;
		while (++find <= len_seek && src[find + i] == seek[find])
		{
			if (find == len_seek - 1)
				return (i + 1);
		}
	}
	return (0);
}

char	*find_var_in_env(char *find, char **env)
{
	char	*g_variable;
	char	*temp;
	int		i;

	i = 0;
	g_variable = NULL;
	temp = NULL;
	i = find_str_in_tab(0, find, env);
	if (!i)
		return (NULL);
	temp = ft_strdup(env[i]);
	if (!temp)
		return (NULL);
	g_variable = ft_strtrim(temp, find);
	if (!g_variable)
		return (NULL);
	s_free(&temp);
	return (g_variable);
}
