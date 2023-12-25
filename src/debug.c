/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:44 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/25 04:49:17 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	db_debug(t_linux *sys_l, void *memm1, void **memm2);

void	db_debug(t_linux *sys_l, void *memm1, void **memm2)
{
	char	*array1;
	char	*array2;

	(void)sys_l;
	(void)memm1;
	(void)memm2;
	array1 = NULL;
	array2 = NULL;
	array1 = readline("DB_DEBUG>> ");
	//array2 = getcwd(array1, 4096);
	printf("You wrote \"%s\"\n", array1);
	fflush(stdout);
	s_free(&array1);
	return ;
}
