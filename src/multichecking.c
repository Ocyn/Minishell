/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multichecking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/26 18:01:17 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	multichecking(const char check, int mode)
{
	if (mode)
		return (0);
	if (mode == 1)
		return (command_pattern(check));
	else if (mode == 2)
		return (white_space(check));
	else
		return (!(white_space(check) && command_pattern(check)));
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
