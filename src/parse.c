/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/11 15:31:48 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	resplit_infile(char ***tab)
{
	char	**temp_tab;
	int		i;

	temp_tab = NULL;
	i = -1;
	while ((*tab) && (*tab)[++i])
	{
		if (find_str_in_str((*tab)[i], "<") \
		&& !find_str_in_str((*tab)[i], "<<"))
		{
			str_edit(&(*tab)[i], "<", " < ");
			temp_tab = ft_split((*tab)[i], ' ');
			insert_tab_in_tab(temp_tab, &(*tab), i + 1);
			free_tab(temp_tab, tablen(temp_tab));
		}
	}
}

void	whitespaces_to_space(char **entry)
{
	str_edit(entry, "\t", " ");
	str_edit(entry, "\0011", " ");
	str_edit(entry, "\0012", " ");
	str_edit(entry, "\0013", " ");
	str_edit(entry, "\0014", " ");
	str_edit(entry, "\0015", " ");
}

char	**get_token(char *cmd_in)
{
	char	**tab;
	char	*temp;

	temp = NULL;
	temp = ft_strtrim(cmd_in, "  \0011\0012\0013\0014\0015\t");
	whitespaces_to_space(&temp);
	str_edit(&temp, ">", " > ");
	str_edit(&temp, ">  >", " >> ");
	str_edit(&temp, "|", " | ");
	tab = split_command(temp, ' ');
	s_free(&temp);
	resplit_infile(&tab);
	return (tab);
}

void	parse(t_linux *shell)
{
	t_cmd	*command;
	char	*cmd_in;
	char	**token;

	command = shell->head;
	token = NULL;
	cmd_in = shell->input;
	if (!cmd_in || !cmd_in[0] || is_empty(cmd_in))
		return ;
	if (!ft_strcmp(cmd_in, "exit"))
		return (ft_exit(shell));
	add_history(cmd_in);
	token = get_token(cmd_in);
	command = build_commands(shell->head, token);
	shell->token = token;
	(void)command;
	/*DEBUG*/ db_display_list(shell->head, "\nTotal Memory Data\n");
	launch_command(shell);
	free_tab(token, tablen(token));
	cmd_free_list(shell->head);
}

void	change_oldpwd(t_linux *shell)
{
	if (shell->oldpwd != NULL)
		free(shell->oldpwd);
	shell->oldpwd = put_in(getcwd(NULL, 0));
}
