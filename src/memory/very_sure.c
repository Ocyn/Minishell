/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   very_sure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 04:31:20 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/12 13:43:48 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	vs_memory_log(void *check, int supposed_state)
{
	t_sdata	*data;

	data = check;
	if (!data)
		return ;
	if (((data->sstr > 0) != supposed_state) || (check != NULL))
		printf("\r   "__INVALID_FREED"\n");
	else
		printf("\r   "__VALID_FREED"\n");
}

void	very_sure(t_sdata *data, unsigned long size)
{
	void	*temp;

	temp = NULL;
	if (data && !size)
	{
		temp = data;
		printf("\tVs free on [%p]:[%d[%s]", data, data->sstr, *data->str);
		if (data->sstr)
			s_free(data->str);
		vs_memory_log(temp, 0);
		data->sstr = 0;
	}
	if (data && size)
	{
		printf("\tVs alloc on size:[%lu]", size);
		if (data->sstr)
			s_free(data->str);
		data->str = s_malloc(size);
		data->sstr = size;
		if (!data->str)
			data->sstr = 0;
		vs_memory_log(data, 1);
	}
	return ;
}


