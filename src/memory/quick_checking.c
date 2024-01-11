/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocyn <ocyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/11 01:31:47 by ocyn             ###   ########.fr       */
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

int	heredoc_check(const char **token, int index, int *checker)
{
	if (find_str_in_str(token[index], "<<") && token[1] \
	&& !find_str_in_str(token[1], "<") \
	&& !find_str_in_str(token[tablen((char **)token)], "<"))
	{
		printf("\n\tHeredoc detected\n");
		if (checker)
			*checker = 1;
		return (1);
	}
	return (0);
}

int	special_char(char *seek, int mode)
{
	if (!seek || !seek[0])
		return (EMPTY_CMD);
	if ((mode <= 0 || mode == INFILE_CMD) \
	&& (str_occur(seek, "<") && !str_occur(seek, "<<")))
		return (INFILE_CMD);
	else if ((mode == -3 || mode == HEREDOC) && str_occur(seek, "<<"))
		return (HEREDOC);
	else if ((mode <= 0 || mode == OUTFILE_CMD) \
	&& str_occur(seek, ">") && !str_occur(seek, ">>"))
		return (OUTFILE_CMD);
	else if ((mode <= 0 || mode == OUTFILE_ADDER) && str_occur(seek, ">>"))
		return (OUTFILE_ADDER);
	else if ((mode <= 0 || mode == PIPE_CMD) && str_occur(seek, "|"))
		return (PIPE_CMD);
	else if ((mode <= 0 || mode == DOLLARSIGN_CMD) && str_occur(seek, "$"))
		return (DOLLARSIGN_CMD);
	else if ((mode == -2 || mode == SIMPLEQUOTE) && str_occur(seek, "\'"))
		return (SIMPLEQUOTE);
	else if ((mode == -2 || mode == DOUBLEQUOTE) && str_occur(seek, "\""))
		return (DOUBLEQUOTE);
	return (SINGLE_CMD);
}

int	white_space(const char seek)
{
	if ((seek >= 9 && seek <= 13) || seek == 32)
		return (1);
	return (0);
}
