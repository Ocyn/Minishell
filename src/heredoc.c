/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:03:13 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 05:49:24 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**add_str_to_tab(char *add, char **tab)
{
	char	**new;
	int		i;

	new = NULL;
	i = 0;
	if (!add)
		return (tab);
	i = tablen(tab) + 1;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = NULL;
	i = -1;
	while (tab[++i])
		new[i] = ft_strdup(tab[i]);
	new[i] = ft_strdup(add);
	free_tab(tab, tablen(tab));
	return (new);
}

void	import_remain(char ***out, int start, char **remain, char *delim)
{
	while (remain[start])
	{
		if (special_char(remain[start], 0))
			return ;
		if (!find_str_in_str(remain[start], "<<") \
		&& ft_strcmp(remain[start], delim))
			*out = add_str_to_tab(remain[start], *out);
		start++;
	}
}

void	import_heardoc(char *line, char ***out, int var_exp)
{
	char	*temp;

	temp = NULL;
	(void)var_exp;
	str_edit(&line, "\"", "\\\"");
	cut_and_paste((void **)&line, (void **)&temp, ft_strlen(line) + 1);
	line = ft_strjoin("\"", temp);
	cut_and_paste((void **)&line, (void **)&temp, ft_strlen(line) + 1);
	line = ft_strjoin(temp, "\"");
	s_free(&temp);
	*out = add_str_to_tab(line, *out);
	s_free(&line);
}

char	**heredocument(char *delim, char **src, int start, char **remain)
{
	char	**out;
	char	*line;
	int		i;
	int		var_exp;

	line = NULL;
	out = src;
	var_exp = 0;
	i = 0;
	if (!delim)
		return (NULL);
	var_exp += (ft_strchr(delim, '\'') != NULL) \
	+ (ft_strrchr(delim, '\'') != NULL);
	db_tabstr_display(remain, "\n\tRemain: ", -1);
	while (delim)
	{
		i++;
		line = readline("heredoc> ");
		if (!ft_strcmp(line, delim))
			break ;
		import_heardoc(line, &out, var_exp);
	}
	import_remain(&out, start, remain, delim);
	db_tabstr_display(out, "\n\tOut: ", -1);
	return (out);
}
