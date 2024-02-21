/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:29 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/21 21:57:38 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// void	err_log(int launch, void (*errormode)(int, char *))
// {
// 	if (!launch)
// 		return ;
// 	printf("minishell: ");
// 	errormode()
// }

void	err_perror(int launch)
{
	if (launch)
	{
		perror("minishell");
		g_sign = 2;
	}
}

void	err_custom(int launch, char *message)
{
	if (launch)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
		g_sign = 2;
	}
}

void	err_parse_token(int launch)
{
	if (launch)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error unexpected token", 2);
		ft_putstr_fd("\n", 2);
		g_sign = 2;
	}
}
