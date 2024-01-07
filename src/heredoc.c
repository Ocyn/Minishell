/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 05:47:51 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 14:21:59 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	hd_parse(t_linux *syst)
{
	t_cmd	*command;
	char	*temp;
	char	*line;

	temp = NULL;
	command = syst->command;
	str_edit(&syst->input, "\"", "\\\"");
	line = syst->input;
	command = cmd_add_unit(command);
	command->command.sraw = ft_strjoin("\"", line);
	cut_and_paste((void **)&command->command.sraw, (void **)&temp \
	, ft_strlen(command->command.sraw) + 1);
	command->command.sraw = ft_strjoin(temp, "\"");
	s_free(&temp);
	syst->command = command;
}

char	**get_heredoc(char *src)
{
	t_linux	heredoc;
	char	**out;
	char	*delim;
	int		i;

	if (!find_str_in_str(src, "<<"))
		return (NULL);
	out = NULL;
	i = ft_strlen(src + find_str_in_str(src, "<<")) \
	- ft_strlen(ft_strchr(src + find_str_in_str(src, "<<"), ' '));
	delim = ft_substr(ft_strchr(src, '<'), 2, i);
	if (!delim || !delim[0] || ft_strchr(delim, '<'))
		return (s_free(&delim), NULL);
	struct_init(&heredoc);
	heredoc.prompt = ft_strdup("heredoc>");
	read_prompt(&heredoc, delim, hd_parse);
	out = list_to_tab(heredoc.head);
	db_display_list(heredoc.head, "\nHeredoc: ");
	s_free(&heredoc.prompt);
	cmd_free_list(heredoc.head);
	free(heredoc.head);
	s_free(&delim);
	return (out);
}
