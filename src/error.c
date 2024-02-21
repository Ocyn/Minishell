/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:29 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/21 13:22:47 by jcuzin           ###   ########.fr       */
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
		printf("minishell: ");
		printf("%s", message);
		printf("\n");
		g_sign = 2;
	}
}

void	err_parse_token(int launch)
{
	if (launch)
	{
		printf("minishell: ");
		printf("syntax error unexpected token");
		printf("\n");
		g_sign = 2;
	}
}
