/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/18 10:22:29 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!white_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	special_char(char *seek, int mode)
{
	if (!seek || !seek[0])
		return (_TOK_EMPTY);
	if ((mode <= 0 || mode == _TOK_INFILE) \
	&& (str_occur(seek, "<") && !str_occur(seek, "<<")))
		return (_TOK_INFILE);
	else if ((mode <= -3 || mode == _TOK_HEREDOC) && str_occur(seek, "<<"))
		return (_TOK_HEREDOC);
	else if ((mode <= 0 || mode == _TOK_OUTFILE) \
	&& str_occur(seek, ">") && !str_occur(seek, ">>"))
		return (_TOK_OUTFILE);
	else if ((mode <= 0 || mode == _TOK_OUTFILE_APP) && str_occur(seek, ">>"))
		return (_TOK_OUTFILE_APP);
	else if ((mode <= 0 || mode == _TOK_PIPE) && str_occur(seek, "|"))
		return (_TOK_PIPE);
	else if ((mode <= 0 || mode == _TOK_EXPAND) && str_occur(seek, "$"))
		return (_TOK_EXPAND);
	else if ((mode <= -2 || mode == _TOK_SP_QUOTE) && str_occur(seek, "\'"))
		return (_TOK_SP_QUOTE);
	else if ((mode <= -2 || mode == _TOK_DB_QUOTE) && str_occur(seek, "\""))
		return (_TOK_DB_QUOTE);
	return (_TOK_WORD);
}

int	white_space(const char seek)
{
	if ((seek >= 9 && seek <= 13) || seek == 32)
		return (1);
	return (0);
}
