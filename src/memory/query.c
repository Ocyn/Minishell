/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 08:00:36 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 01:46:12 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// static t_query	*seek_patterns(t_query *input, t_query (*ask)(t_query))
// {
// 	input->index = 0;
// 	input.
// }

// static t_query	*get_patterns(t_query *input, t_query (*ask)(t_query))
// {
// 	input->index
	
// }

t_query	query(t_query input, t_query (*ask)(t_query))
{
	t_query	out;

	out.id = 0;
	out.start = 0;
	out.end = 0;
	out.boolean = 0;
	out.index = 0;
	out.len = 0;
	out.range = 0;
	out.str = NULL;
	out.tab = NULL;
	out.pattern = NULL;
	out = ask(input);
	return (out);
}
