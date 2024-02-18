/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_scan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:49:05 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/18 08:47:55 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	find_str_in_tab(int strict_mode, char *find, char **tab)
{
	int	i;

	i = -1;
	if (!find || !tab)
		return (-1);
	while (find && tab && tab[++i])
	{
		if (find_str_in_str(tab[i], find))
			if (!strict_mode || (strict_mode && !ft_strcmp(tab[i], find)))
				return (i);
	}
	return (-1);
}

int	find_str_in_str(const char *src, const char *seek)
{
	int	i;
	int	find;

	i = 0;
	if (!src || !seek)
		return (-1);
	while (src[i])
	{
		find = 0;
		while (src[find + i] && src[find + i] == seek[find])
		{
			find++;
			if (!seek[find])
				return (i);
		}
		i++;
	}
	return (-1);
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

int	how_many_occur(char *src, char *seek)
{
	char	*temp;
	int		occur;
	int		i;

	occur = 0;
	temp = src;
	while (temp && temp[0] && seek)
	{
		i = find_str_in_str(temp, seek);
		if (i == -1)
			break ;
		temp += (i + ft_strlen(seek));
		occur++;
	}
	return (occur);
}
