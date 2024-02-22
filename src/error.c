/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:29 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/22 10:52:47 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	err_perror(int launch)
{
	if (launch)
	{
		perror("minishell");
		g_sign = 2;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	err_custom(int launch, char *message)
{
	if (launch)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
		g_sign = 2;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	err_parse_token(int launch)
{
	if (launch)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error unexpected token", 2);
		ft_putstr_fd("\n", 2);
		g_sign = 2;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
