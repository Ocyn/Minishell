/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:22:27 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/12 14:40:17 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_echo(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0)
		{
			if (i > 1)
				printf(" ");
			printf ("%s", str[i]);
		}
		i++;
	}
	printf ("\n");
}

//ajout du  -n a faire