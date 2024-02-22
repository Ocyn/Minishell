/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:00:21 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/22 14:12:26 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_exit(t_linux *shell)
{
	int	i;

	i = 0;
	while (shell->head->next->meta.raw[i])
		i++;
	if (i == 2)
	{
		shell->end = 1;
		g_sign = ft_atoi(shell->head->next->meta.raw[1]);
	}
	if (i <= 2)
		shell->end = 1;
	if (i > 2)
		err_custom(1, "exit: too many arguments");
}
