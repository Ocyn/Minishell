/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:29 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/20 16:54:17 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	err_custom(int launch, char *message)
{
	if (launch)
	{
		printf("minishell: ");
		printf("%s", message);
		printf("\n");
	}
}

void	err_parse_token(int launch)
{
	if (launch)
	{
		printf("minishell: ");
		printf("syntax error unexpected token");
		printf("\n");
	}
}
