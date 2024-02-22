/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:00:21 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/22 15:50:38 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_exit(t_cmd *cmd, t_linux *shell)
{
	int	i;

	i = 0;
	while (cmd->meta.raw[i])
		i++;
	if (i == 2)
	{
		shell->end = 1;
		g_sign = ft_atoi(cmd->meta.raw[1]);
	}
	if (i <= 2)
		shell->end = 1;
	if (i > 2)
		ft_putstr_fd ("minishell: exit: too many arguments\n", 2);
}
