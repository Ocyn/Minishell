/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 05:47:51 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/03 09:10:28 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	insert_tab_in_tab(char **insert, char **tab, int where)
{
	char	**new;
	int		ins_;
	int		i;
	int		len;

	i = -1;
	ins_ = 0;
	new = NULL;
	len = tablen(tab);
	printf("\t\t where: %d", where);
	if (!insert || !len || len < where)
		return ;
	new = s_malloc(sizeof(char *) * (len + tablen(insert) + 1));
	if (!new)
		return ;
	while (++i >= 0 && tab[i - ins_])
	{
		printf("\t\t tab [%s]", tab[i - ins_]);
		db_tabstr_display(new);
		printf("\n");
		if (i == where)
			while (++i >= 0 && insert[ins_])
				new[i] = ft_strdup(insert[ins_++]);
		new[i] = ft_strdup(tab[i - ins_]);
	}
	printf("\t\tEnd: ");
	db_tabstr_display(new);
	printf("\n");
	free_tab(tab, len);
	tab = new;
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
	printf("\n\t len = %d\n", len);
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
	s_free(&heredoc.prompt);
	out = list_to_tab(heredoc.head);
	db_display_list(heredoc.head);
	cmd_free_list(heredoc.head);
	free(heredoc.head);
	s_free(&delim);
	(void)out;
	(void)src;
	return (out);
}

