/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/20 14:57:09 by jcuzin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	skip_until(char **tab, int mode, int (*stop)(char *, int));

int	type_identifier(char **src, int len)
{
	char	**raw;
	int		type;

	type = -1;
	raw = tab_dup(src, len);
	if (find_str_in_tab(1, "<", raw) != -1)
		type = INFILE_CMD;
	else if (find_str_in_tab(1, ">", raw) != -1)
		type = OUTFILE_CMD;
	else if (find_str_in_tab(1, "|", raw) != -1)
		type = PIPE_CMD;
	else if (find_str_in_tab(1, "$", raw) != -1)
		type = DOLLARSIGN_CMD;
	else if (find_str_in_tab(1, ">>", raw) != -1)
		type = OUTFILE_ADDER;
	else if (find_str_in_tab(0, "<<", raw) != -1)
		type = HEREDOC;
	else if (raw && raw[0])
		type = SINGLE_CMD;
	free_tab(raw, len);
	return (type);
}

// ft_function_to_get_infile_and_outfile

t_cmd	*define_command_pattern(t_cmd *cmd, char **token, int i, int len)
{
	int		type;

	(void)type;
	type = type_identifier(token + i, len);
	cmd->command.raw = tab_dup(token + i, len);
	//Infile & outfile include function
	cmd->command.exec_cmd = tab_dup(cmd->command.raw + 1, len);
	return (cmd);
}

t_cmd	*build_commands(t_cmd *command, char **token)
{
	int		i;
	int		input_len;
	int		token_len;

	/*DEBUG*/	db_print_custom_font("Build command\n", FE_UND);
	i = 0;
	token_len = 0;
	input_len = tablen(token);
	while (i <= input_len && token && token[i])
	{
		/*DEBUG*/	db_tabstr_display(token, "\n\tToken Input (i)", i);
		token_len = skip_until(token + i, 0, special_char);
		command = cmd_add_unit(command);
		command = define_command_pattern(command, token, i, token_len);
		if (!command->command.exec_cmd && !command->command.raw && !command->command.env_var)
			cmd_rm_unit(command);
		i += token_len;
		/*DEBUG*/	db_print_custom_font("\n\tEnd loop\t: ", FE_BOL);
		/*DEBUG*/	printf("i [%d] | input_len [%d]\n", i, input_len);
	}
	return (command);
}
