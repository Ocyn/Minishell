/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multichecking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/01 16:58:28 by jcuzin           ###   ########.fr       */
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
	if (str_occur(token[index], "<<") && token[1] \
	&& !str_occur(token[1], "<") \
	&& !str_occur(token[tablen((char **)token)], "<"))
	{
		printf("\n\tHeredoc detected\n");
		if (checker)
			*checker = 1;
		return (1);
	}
	return (0);
}

int	str_occur(const char *src, const char *seek)
{
	int	i;
	int	len_src;
	int	len_seek;

	i = 0;
	if (!src || !seek)
		return (0);
	len_src = (int)ft_strlen(src);
	len_seek = (int)ft_strlen(seek);
	while (i < len_src && i < len_seek && src[i] && src[i] == seek[i])
		i++;
	if (i == len_seek)
		return (1);
	return (0);
}

int	command_pattern(const char	*seek)
{
	if (!seek || !seek[0])
		return (EMPTY_CMD);
	if (str_occur(seek, "<") && !str_occur(seek, "<<"))
		return (INFILE_CMD);
	else if (str_occur(seek, ">") && !str_occur(seek, ">>"))
		return (OUTFILE_CMD);
	else if (str_occur(seek, ">>"))
		return (OUTFILE_ADDER);
	else if (str_occur(seek, "|"))
		return (PIPE_CMD);
	else if (str_occur(seek, "$"))
		return (DOLLARSIGN_CMD);
	return (SINGLE_CMD);
}

int	white_space(const char seek)
{
	if ((seek >= 9 && seek <= 13) || seek == 32)
		return (1);
	return (0);
}
