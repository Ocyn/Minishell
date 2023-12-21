/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/21 21:29:23 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_debug(t_linux *sys_l, void *memm1, void **memm2);

void	db_debug(t_linux *sys_l, void *memm1, void **memm2)
{
	char	*local_array;
	int		*nb_array;

	(void)sys_l;
	(void)memm1;
	(void)memm2;
	(void)local_array;
	local_array = NULL;
	nb_array = NULL;
	printf("DB_DEBUG\n");
	local_array = (char *)s_malloc(sizeof(char) * (9 + 1));
	nb_array = s_malloc(sizeof(int) * 9);
	s_free((void *)&local_array);
	s_free((void *)&nb_array);
	return ;
}
