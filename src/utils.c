/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:24 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/29 00:01:11 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*tab_to_str(char **tab)
{
	char	*out;
	int		len;
	int		i;

	i = 0;
	len = 0;
	out = NULL;
	while (tab[i])
		len += ft_strlen(tab[i++]);
	out = s_malloc(sizeof(char) * (len + 1));
	i = -1;
	while (tab[++i])
		ft_strlcat(out, tab[i], ft_strlen(tab[i]));
	free_tab(tab, tablen(tab));
	return (out);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && s2)
		return (-1);
	if (s1 && !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*get_path(char *command, char **env)
{
	char	*cmd_path;
	char	*check;
	char	**var;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp(env[i], "PATH=", 5) != 0)
		return (NULL);
	cmd_path = ft_strtrim(env[i], "PATH=");
	var = ft_split(cmd_path, ':');
	s_free(&cmd_path);
	i = -1;
	check = ft_strjoin("/", command);
	while (var[++i])
	{
		cmd_path = ft_strjoin(var[i], check);
		if (!access(cmd_path, F_OK))
			break ;
		s_free(&cmd_path);
	}
	if (!cmd_path)
		cmd_path = command;
	return (free_tab(var, tablen(var)), s_free(&check), cmd_path);
}
