/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:15:34 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/22 15:43:22 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_env(t_env *env)
{
	t_env	*buf;

	buf = env;
	while (buf->next != NULL)
	{
		if (ft_strchr(buf->str, '=') != NULL)
			printf ("%s\n", buf->str);
		buf = buf->next;
	}
	if (ft_strchr(buf->str, '=') != NULL)
		printf ("%s\n", buf->str);
	g_sign = 0;
}
