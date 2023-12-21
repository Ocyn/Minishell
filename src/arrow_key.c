/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:18:36 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/21 23:23:30 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

#define UP_ARROW 					"[A"
#define DOWN_ARROW					"[B"
#define NEXT_HISTORY				"C-N"  
#define PREVIOUS_HISTORY            "C-P"  
#define CTRL_D 						1
#define CTRL_C 						1

int	nav_maincore(t_linux *data, char *cmd_in);
int	nav_scroll_up(t_linux *data, char *cmd_in);
int	nav_scroll_down(t_linux *data, char *cmd_in);
int	nav_ctrl_c(t_linux *data, char *cmd_in);
int	nav_ctrl_d(t_linux *data, char *cmd_in);

int	nav_maincore(t_linux *data, char *cmd_in)
{
	(void)data;
	(void)cmd_in;
	if (cmd_in == UP_ARROW)
		nav_scroll_up(data, cmd_in);
	else if (cmd_in == DOWN_ARROW)
		nav_scroll_down(data, cmd_in);
	else if (cmd_in == CTRL_C)
		nav_ctrl_c(data, cmd_in);
	else if (cmd_in == CTRL_D)
		nav_ctrl_d(data, cmd_in);
	else
		return (0);
}
