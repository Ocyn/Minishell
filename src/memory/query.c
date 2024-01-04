/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 08:00:36 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/04 09:00:37 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_query	query(t_query input, t_query (*ask)(t_query))
{
	t_query	out;

	out.boolean = 0;
	out.index = 0;
	out.len = 0;
	out.range = 0;
	out.str = NULL;
	out.stemp = NULL;
	out.tab = NULL;
	out.ttemp = NULL;
	out = ask(input);
	return (out);
}
