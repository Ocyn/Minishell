/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:29 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/23 04:06:05 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_unclosed_quotes(char *tab)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (tab[i])
	{
		quotes_check_parse(tab[i], &quotes);
		i++;
	}
	if (quotes != 0)
		return (1);
	return (0);
}

int	err_perror(int launch)
{
	if (launch)
	{
		perror("minishell");
		g_sign = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	err_custom(int launch, char *message, int sig)
{
	if (launch)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
		g_sign = sig;
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
