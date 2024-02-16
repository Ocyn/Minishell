/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/11 06:28:22 by jcuzin             ###   ########.fr       */
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
	else if ((mode <= 0 || mode == _TOK_OUTFILE_APPEND) && str_occur(seek, ">>"))
		return (_TOK_OUTFILE_APPEND);
	else if ((mode <= 0 || mode == _TOK_PIPE) && str_occur(seek, "|"))
		return (_TOK_PIPE);
	else if ((mode <= 0 || mode == _TOK_DOLLARSIGN) && str_occur(seek, "$"))
		return (_TOK_DOLLARSIGN);
	else if ((mode <= -2 || mode == _TOK_SIMPLEQUOTE) && str_occur(seek, "\'"))
		return (_TOK_SIMPLEQUOTE);
	else if ((mode <= -2 || mode == _TOK_DOUBLEQUOTE) && str_occur(seek, "\""))
		return (_TOK_DOUBLEQUOTE);
	return (_TOK_SINGLE_WORD);
}

int	white_space(const char seek)
{
	if ((seek >= 9 && seek <= 13) || seek == 32)
		return (1);
	return (0);
}
