/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:22:27 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/14 17:24:47 by aammirat         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_echo(t_linux *shell)
{
	int	i;

	i = 4;
	while (shell->history[shell->nb_history - 1][i])
	{
		write (1, &shell->history[shell->nb_history - 1][i], 1);
		i++;
	}
}
