/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 10:49:42 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	skip_until(char **tab, int mode, int (*stop)(char *, int));

int	get_prefixes(char **src, char ***prefixes)
{
	char	*temp;
	char	*pre_extract;
	int		stop;

	pre_extract = NULL;
	temp = NULL;
	if (!src)
		return (0);
	stop = skip_until(src, -2, special_char);
	if (find_str_in_tab(0, "<<", src) != -1 \
	&& find_str_in_tab(0, "<<", src) < stop)
		stop = find_str_in_tab(0, "<<", src);
	pre_extract = tab_to_str(src, stop, 1, 0);
	temp = ft_strdup(pre_extract);
	if (!temp)
		return (0);
	s_free(&pre_extract);
	printf("\n\t\tTemp = [%s]\n", temp);
	*prefixes = ft_split(temp, ' ');
	s_free(&temp);
	return (tablen(*prefixes));
}

char	**get_args(char **token, int start)
{
	char	**full;
	char	**heredoc;
	int		hd_index;
	int		args_len;

	args_len = 0;
	hd_index = -1;
	full = NULL;
	heredoc = NULL;
	args_len = tablen(token) - start;
	printf("\n\tlen_Token [%d] - Start [%d] == ArgLen [%d]\n", tablen(token), start, args_len);
	args_len -= (special_char(token[args_len + start], 0) != -1);
	if (token && token[start] && args_len)
	{
		full = tab_dup(token + start, args_len);
		hd_index = find_str_in_tab(0, "<<", full);
		printf("\n\t\tHd_index [%d]", hd_index);
	}
	if (full && hd_index >= 0)
	{
		heredoc = get_heredoc(full[hd_index], 0);
		insert_tab_in_tab(heredoc, &full, hd_index + 1);
		free_tab(heredoc, tablen(heredoc));
	}
	return (full);
}

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

t_cmd	*define_command_pattern(t_cmd *cmd, char **token, int i, int len)
{
	int	prefixes_len;

	prefixes_len = 0;
	len -= (cmd->type == OUTFILE_CMD || cmd->type == OUTFILE_ADDER);
	len += (cmd->type == INFILE_CMD);
	if (cmd->prev && (cmd->prev->type == OUTFILE_CMD \
	|| cmd->prev->type == OUTFILE_ADDER))
	{
		cmd->type = cmd->prev->type;
		cmd->prev->type = SINGLE_CMD;
		i -= (i > 0 && token[i - 1]);
	}
	cmd->command.raw = tab_dup(token + i, len);
	get_prefixes(cmd->command.raw, &cmd->command.prefixes);
	prefixes_len = tablen(cmd->command.prefixes);
	cmd->command.args = get_args(cmd->command.raw, prefixes_len);
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
		command->type = type_identifier(token + i, token_len);
		command = define_command_pattern(command, token, i, token_len);
		i += token_len + (command->type == INFILE_CMD);
		db_print_custom_font("\n\tEnd loop\t: ", FE_BOL);
		/*DEBUG*/	printf("i [%d] | input_len [%d]\n", i, input_len);
	}
	return (command);
}
