/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:22:27 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/11 16:01:09 by aammirat         ###   ########.fr       */
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
			printf ("%s",str[i]);
		i++;
	}
	
}

//ajout du  -n a faire