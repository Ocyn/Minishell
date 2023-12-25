/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:18:36 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/24 20:35:11 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

#define UP_ARROW 					"[A"
#define DOWN_ARROW					"[B"
#define NEXT_HISTORY				"C-N"  
#define PREVIOUS_HISTORY            "C-P"  
#define CTRL_D 						"unknown"
#define CTRL_C 						"unknown"

int	nav_maincore(t_linux *data, char *cmd_in)
{
	(void)data;
	(void)cmd_in;
	return (0);
}
