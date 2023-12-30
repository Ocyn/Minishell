/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multichecking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/29 21:25:38 by jcuzin           ###   ########.fr       */
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

int	command_pattern(const char seek)
{
	if (seek == '<')
		return (INFILE_CMD);
	else if (seek == '>')
		return (OUTFILE_CMD);
	else if (seek == '|')
		return (PIPE_CMD);
	else if (seek == '$')
		return (DOLLARSIGN_CMD);
	return (SINGLE_CMD);
}

int	white_space(const char seek)
{
	if ((seek >= 9 && seek <= 13) || seek == 32)
		return (1);
	return (0);
}
