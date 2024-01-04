/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 05:49:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/04 07:43:11 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	get_prefixes(char **src, char ***prefixes)
{
	char	*temp;
	int		stop;

	stop = 0;
	temp = NULL;
	if (!src)
		return (0);
	temp = NULL;
	stop = find_str_in_tab(0, "\"", src);
	if (stop > find_str_in_tab(0, "\'", src))
		stop = find_str_in_tab(0, "\'", src);
	temp = tab_to_str(src, stop, 1, 0);
	if (!temp)
		return (0);
	*prefixes = ft_split(temp, ' ');
	if (!*prefixes)
		return (0);
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
	while (++i <= token_len)
		raw[i] = ft_strdup(token_tab[i]);
	return (raw);
}

int	skip_until(char **tab, int (*stop)(char *))
{
	int	len;
	int	i;

	i = 0;
	len = tablen(tab);
	while (tab[i] && !stop(tab[i]))
		i++;
	if (i == len)
		return (i);
	return (0);
}

char	**get_args(char **token)
{
	char	**full;
	int		i;

	i = 0;
	full = NULL;
	(void)token;
	(void)i;
	return (full);
}

t_cmd	*build_commands(t_cmd *command, char **token)
{
	char	**entry;
	int		i;
	int		token_len;

	i = 0;
	token_len = 0;
	entry = NULL;
	while (i <= token_len && token && token[i])
	{
		token_len = skip_until(token + i, special_char);
		db_tabstr_display(token, "\n\tToken", token_len);
		command = cmd_add_unit(command);
		entry = tab_dup(token, token_len);
		db_tabstr_display(entry, "\n\tEntry", -1);
		get_prefixes(entry, &command->command.prefixes);
		command->command.args = get_args(entry);
		free_tab(entry, tablen(entry));
		i += token_len + (token_len <= 0);
	}
	return (command);
}
