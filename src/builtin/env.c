/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:15:34 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/30 18:36:58 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_env(t_linux *shell)
{
	t_env	*buf;

	buf = shell->env;
	while (buf->next != NULL)
	{
		printf ("%s\n", buf->str);
		buf = buf->next;
	}
	printf ("%s\n", buf->str);
	g_sign = 0;
}
