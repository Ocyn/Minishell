/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/03 03:06:40 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

int	command_pattern(const char	*seek)
{
	if (!seek || !seek[0])
		return (EMPTY_CMD);
	if (find_str_in_str(seek, "<") && !find_str_in_str(seek, "<<"))
		return (INFILE_CMD);
	else if (find_str_in_str(seek, ">") && !find_str_in_str(seek, ">>"))
		return (OUTFILE_CMD);
	else if (find_str_in_str(seek, ">>"))
		return (OUTFILE_ADDER);
	else if (find_str_in_str(seek, "|"))
		return (PIPE_CMD);
	else if (find_str_in_str(seek, "$"))
		return (DOLLARSIGN_CMD);
	return (SINGLE_CMD);
}

int	white_space(const char seek)
{
	if ((seek >= 9 && seek <= 13) || seek == 32)
		return (1);
	return (0);
}
