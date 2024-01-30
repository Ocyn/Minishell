/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:02:04 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/30 18:37:24 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_pwd(void)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (temp)
	{
		printf ("%s\n", temp);
		s_free(&temp);
		g_sign = 0;
	}
	else
	{
		g_sign = 1;
		printf ("where am i\n");
	}
}
