/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:00:21 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/17 22:14:56 by aammirat         ###   ########.fr       */
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
		printf ("bash: exit: too many arguments\n");
}
