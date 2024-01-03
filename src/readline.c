/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:44:24 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/03 12:45:30 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "../header/text_codes.h"

void	read_prompt(t_linux *ssystem, char *exit, void (*pa)(t_linux *))
{
	if (!exit)
		return ;
	printf("\n\nType\t");
	printf(""HIGHLIGHT_TEXT"%s"FONT_RESET" to exit\n\n", exit);
	while (exit)
	{
		ssystem->input = readline(ssystem->prompt);
		if (!ft_strcmp(ssystem->input, exit))
			return ((void)s_free(&ssystem->input));
		pa(ssystem);
		s_free(&ssystem->input);
	}
}
