/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/21 18:29:41 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_debug(t_linux *sys_l, void *memm1, void **memm2)
{
	char	*local_array;

	(void)sys_l;
	(void)memm1;
	(void)memm2;
	(void)local_array;
	local_array = NULL;
	printf("DB_DEBUG\n");
	local_array = s_malloc(sizeof(char) * );
	return ;
}
