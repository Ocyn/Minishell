/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:02:04 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 04:42:10 by jcuzin           ###   ########.fr       */
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
	}
	else
		printf ("where am i\n");
}
