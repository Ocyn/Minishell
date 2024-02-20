/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/20 20:15:34 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_str(char *str, int (*check)(const char))
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!check(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_tab(char **tab, int (*check)(const char))
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!is_str(tab[i], check))
			return (0);
		i++;
	}
	return (1);
}

int	is_special_token(const char seek)
{
	if (seek)
	{
		if (seek == '<' || seek == '>' || seek == '|' || seek == ' ')
			return (1);
	}
	return (0);
}

int	is_white_space(const char seek)
{
	if (seek)
	{
		if ((seek >= 9 && seek <= 13) || seek == 32)
			return (1);
	}
	return (0);
}
