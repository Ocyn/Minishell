/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:15:34 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/12 14:44:05 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_env(t_linux *shell)
{
	int	i;

	i = 0;
	while (shell->envi && shell->envi[i])
	{
		printf("%s\n", shell->envi[i]);
		i++;
	}
}
