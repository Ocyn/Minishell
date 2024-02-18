/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/18 16:27:49 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strtok(char *src, char delim)
{
	int	id;

	id = 0;
	if (src && delim)
	{
		src = ft_strchr(src, delim);
		src += (src && src[0] &&src[1]);
		while (src && src[id] && src[id] != delim)
			id++;
		src[id] = 0;
	}
	return (src);
}

void	whitespaces_to_space(char **entry)
{
	str_edit(entry, "\t", " ");
	str_edit(entry, "\n", " ");
	str_edit(entry, "\v", " ");
	str_edit(entry, "\r", " ");
}

char	**rm_quotes_in_tab(char **tab, char quote)
{
	t_lst	*list;
	char	**temp;
	char	*tok;
	int		id;

	temp = NULL;
	tok = NULL;
	/*DEBUG*/	db_tabstr_display(tab, "\t\tTab input", -1);
	if (!tab || !quote)
		return (NULL);
	list = lst_tab_to_list(tab);
	db_display_list(list, "List of tab", 's');
	while (list)
	{
		temp = multisplit((char *)list->data, " ");
		id = -1;
		while (temp && temp[++id])
		{
			tok = ft_strtok(temp[id], quote);
			
				
		}
		
	}
	return (tab);
}

char	**split_pipeline(char *cmd_in)
{
	char	**tab;
	char	*temp;

	temp = NULL;
	temp = ft_strtrim(cmd_in, "  \n\v\r\t");
	whitespaces_to_space(&temp);
	str_edit(&temp, "|", " | ");
	tab = multisplit(temp, "|");
	//Supprimer double quotes
	db_tabstr_display(tab, "Input splitted before rm DB", 0);
	tab = rm_quotes_in_tab(tab, '\"');
	db_tabstr_display(tab, "Input splitted afte rm DB", 0);
	//faire une fonction qui detecter les repetition consecutives de <, > ou | et envoyer parse error dans ce cas la
	s_free(&temp);
	return (tab);
}

void	parse(t_linux *shell)
{
	t_cmd	*command;
	char	*cmd_in;
	char	**token;

	(void)command;
	command = shell->head;
	token = NULL;
	cmd_in = shell->input;
	if (!cmd_in || !cmd_in[0] || is_empty(cmd_in))
		return ;
	if (!ft_strcmp(cmd_in, "exit"))
		return (ft_exit(shell));
	add_history(cmd_in);
	token = split_pipeline(cmd_in);
	command = build_commands(shell->head, token);
	shell->token = token;
	/*DEBUG*/ db_display_list_cmd(shell->head, "\nTotal Memory Data\n");
	change_env_arg(shell->head->next->meta.raw, shell->env);
	//supprimer simples
	//launch_command(shell, NULL);
	free_tab(token, tablen(token));
	db_cmd_free_list(shell->head);
}
