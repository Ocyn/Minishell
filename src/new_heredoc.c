/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 05:47:51 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/03 16:16:18 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	command->command.raw = ft_strjoin("\"", line);
	cut_and_paste((void **)&command->command.raw, (void **)&temp, ft_strlen(command->command.raw) + 1);
	command->command.raw = ft_strjoin(temp, "\"");
	s_free(&temp);
	printf("HD_DEBUG | Saved to cell %d: [%s]\n", command->id, command->command.raw);
	syst->command = command;
}

char	**list_to_tab(t_cmd *list)
{
	char	**tab;
	int		len;
	int		i;

	i = -1;
	len = list_len(*list);
	tab = NULL;
	if (!list || !list->next)
		return (NULL);
	if (list->id == 0)
		list = list->next;
	tab = s_malloc(sizeof(char *) * len);
	if (!tab)
		return (NULL);
	while (++i > -1 && list)
	{
		tab[i] = ft_strdup(list->command.raw);
		list = list->next;
	}
	return (tab);
}

char	**new_heredoc(char *src)
{
	t_linux	heredoc;
	char	*delim;
	int		i;
	char	**out;

	out = NULL;
	printf("\n\tNewHd DB src [%s] -> %d\n", src, find_str_in_str(src, "<<"));
	if (!find_str_in_str(src, "<<"))
		return (NULL);
	i = ft_strlen(src + find_str_in_str(src, "<<")) - ft_strlen(ft_strchr(src + find_str_in_str(src, "<<"), ' '));
	delim = ft_substr(ft_strchr(src, '<'), 2, i);
	printf("\n\tDelim [%s] -> %d\n", delim, i);
	str_edit(&delim, " ", "");
	if (!delim || !delim[0])
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
	(void)out;
	(void)src;
	return (out);
}

