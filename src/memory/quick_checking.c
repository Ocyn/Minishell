/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 03:22:23 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/20 19:20:21 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_str_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_white_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_tab_empty(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!is_str_empty(tab[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_special_token(const char seek)
{
	if (seek)
	{
		if (seek == '<' || seek == '>' || seek == '|')
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
