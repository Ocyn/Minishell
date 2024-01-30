/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:22:27 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/30 16:10:45 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	test_option(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != '-')
			return (0);
		else if (i == 1 && str[i] != 'n')
			return (0);
		i++;
	}
	if (i == 2)
		return (1);
	return (0);
}

void	ft_echo(char **str)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (!ft_strcmp(str[1], "$?"))
		printf ("%d \n", g_sign);
	while (str[i])
	{
		if (i > 0)
		{
			if (i > 2 || (i == 2 && option == 0))
				printf(" ");
			if (i == 1 && test_option(str[i]))
				option = 1;
			else
				printf ("%s", str[i]);
		}
		i++;
	}
	if (option != 1)
		printf ("\n");
	g_sign = 0;
}
