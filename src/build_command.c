/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 07:34:15 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	skip_until(char **tab, int (*stop)(char *, int));

int	get_prefixes(char **src, char ***prefixes)
{
	char	*temp;
	char	*pre_extract;
	int		stop;

	pre_extract = NULL;
	temp = NULL;
	if (!src)
		return (0);
	stop = skip_until(src, special_char);
	if (find_str_in_tab(0, "\"", src) && stop > find_str_in_tab(0, "\"", src))
		stop = find_str_in_tab(0, "\"", src);
	else if (find_str_in_tab(0, "\'", src) \
	&& stop > find_str_in_tab(0, "\'", src))
		stop = find_str_in_tab(0, "\'", src);
	pre_extract = tab_to_str(src, stop, 1, 0);
	if (ft_strlen(pre_extract) > 1)
		temp = ft_strtrim(pre_extract, "<>|;");
	else
		temp = ft_strdup(pre_extract);
	if (!temp)
		return (0);
	s_free(&pre_extract);
	*prefixes = ft_split(temp, ' ');
	s_free(&temp);
	return (tablen(*prefixes));
}

char	**tab_dup(char **token_tab, int token_len)
{
	char	**raw;
	int		i;

	i = -1;
	raw = NULL;
	raw = s_malloc(sizeof(char *) * (token_len + 1));
	while (++i < token_len)
		raw[i] = ft_strdup(token_tab[i]);
	db_tabstr_display(raw, "\n\tTab_Dup - Out", token_len);
	return (raw);
}

int	skip_until(char **tab, int (*stop)(char *, int))
{
	int	len;
	int	i;

	i = 0;
	len = tablen(tab);
	while (i < len && tab[i] && !stop(tab[i], 0))
		i++;
	i += (stop(tab[i], 0) != 0);
	return (i);
}

char	**get_args(char **token, int start)
{
	char	**full;
	int		args_len;

	args_len = 0;
	full = NULL;
	db_tabstr_display(token, "\n\tGet Args Entry", start);
	args_len = tablen(token) - start;
	args_len -= (special_char(token[args_len + start - 1], 0) != 0);
	if (token && token[start] && args_len)
		full = tab_dup(token + start, args_len);
	return (full);
}

int	type_identifier(char **raw, char **prefixes, char **args)
{
	int	i;
	int	type;

	i = 0;
	type = -1;
	(void)i;
	(void)prefixes;
	(void)args;
	if (find_str_in_tab(1, "<", raw))
		type = INFILE_CMD;
	else if (find_str_in_tab(1, ">", raw))
		type = OUTFILE_CMD;
	else if (find_str_in_tab(1, "|", raw))
		type = PIPE_CMD;
	else if (find_str_in_tab(1, "$", raw))
		type = DOLLARSIGN_CMD;
	else if (find_str_in_tab(1, ">>", raw))
		type = OUTFILE_ADDER;
	else if (find_str_in_tab(0, "<<", raw))
		type = HEREDOC;
	else if (raw && raw[0])
		type = SINGLE_CMD;
	return (type);
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
		token_len = skip_until(token + i, special_char);
		command = cmd_add_unit(command);
		command->command.raw = tab_dup(token + i, token_len);
		/*DEBUG*/	db_tabstr_display(command->command.raw, "\n\tType identifier", token_len - (token_len > 0) - (i + token_len >= input_len));
		command->type = type_identifier(command->command.raw, command->command.prefixes, command->command.args);
		get_prefixes(command->command.raw, &command->command.prefixes);
		command->command.args = get_args(command->command.raw, tablen(command->command.prefixes));
		i += token_len;
		db_print_custom_font("\n\tEnd loop:", FE_BOL);
		/*DEBUG*/	printf(" i [%d] | input_len [%d]\n", i, input_len);
	}
	return (command);
}
