/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:22:27 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/21 21:13:18 by aammirat         ###   ########.fr       */
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
		else if (i > 0 && str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	write_to_shell(int writed, int i, char **str)
{
	if (writed == 0)
		printf(" ");
	printf ("%s", str[i]);
	writed = 0;
	return (writed);
}

void	ft_echo(char **str)
{
	int	i;
	int	option;
	int	writed;

	i = 0;
	writed = 1;
	option = 0;
	while (str[i])
	{
		if (i > 0)
		{
			if (writed == 1 && test_option(str[i]))
				option = 1;
			else
				writed = write_to_shell(writed, i, str);
		}
		i++;
	}
	if (option != 1)
		printf ("\n");
	g_sign = 0;
}
