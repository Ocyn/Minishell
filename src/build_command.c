/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/09 14:04:30 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	get_type(char *src, char *type)
{
	int	i;

	i = -1;
	i = find_str_in_str(src, type);
	if (!src || !type || i == -1)
		return (0);
	// Checker si y'a au moins un char imprimable apres le type
	// Renvoyer erreur "parse" si echec
	return (1);
}

t_cmd	*get_redirection(t_cmd *cmd, char *token)
{
	int	i;

	i = 0;
	(void)cmd;
	(void)token;
	(void)i;
	printf("\nGet_Redirection\n");
	// DISCONNECTED TO PREVENT CRASH ON COMPILING
	/*	
	if (get_type(token, "<"))
		cmd->meta.infile = set_infile(ft_strrchr(token, '<'), 0);
	if (get_type(token, "<<"))
		cmd->meta.infile = set_outfile(ft_strrchr(token, '<'), 0);
	*/
	
	// OUTFILE APPEND AND HEREDOC NOT DONE
	// if (get_type(token, ">"))
	// 	cmd->meta.infile = 
	// if (get_type(token, ">>"))
	// 	cmd->meta.infile = 
	// Missing ">>" alias outfile append (no overwrite) case
	return (cmd);
}

t_cmd	*set_command_metadatas(t_cmd *cmd, char *token)
{
	cmd->meta.raw = tab_dup(token, ft_strlen(token));
	//get_redirection(cmd, token);
	//Infile & outfile include function
	cmd->meta.exec_cmd = tab_dup(cmd->meta.raw, ft_strlen(token));
	return (cmd);
}

t_cmd	*build_commands(t_cmd *command, char **tokens)
{
	int		i;
	int		input_len;
	int		token_len;

	/*DEBUG*/	db_print_custom_font("Build command\n", FE_UND);
	i = 0;
	token_len = 0;
	input_len = tablen(tokens);
	while (i <= input_len && tokens && tokens[i])
	{
		/*DEBUG*/	db_tabstr_display(tokens, "\n\tToken Input (i)", i);
		command = cmd_add_unit(command);
		command = set_command_metadatas(command, tokens[i]);
		if (!command->meta.exec_cmd && !command->meta.raw)
			cmd_rm_unit(command);
		i += token_len;
		/*DEBUG*/	db_print_custom_font("\n\tEnd loop\t: ", FE_BOL);
		/*DEBUG*/	printf("i [%d] | input_len [%d]\n", i, input_len);
	}
	return (command);
}
