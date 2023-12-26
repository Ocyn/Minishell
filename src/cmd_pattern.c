/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pattern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 00:50:38 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/26 00:53:27 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	command_pattern(const char *seek, const char *patern, int type)
{
	int			i;
	int			seek_l;
	int			patern_l;

	i = 0;
	seek_l = ft_strlen(seek);
	patern_l = ft_strlen(patern);
	while (seek[i] && i <= seek_l - patern_l)
	{
		if (!ft_strncmp(seek + i, patern, patern_l))
			return (1);
		i++;
	}
	return (0);
}

