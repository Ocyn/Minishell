/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocyn <ocyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:44:24 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/10 21:42:28 by ocyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "../header/define_syntax.h"

void	read_prompt(t_linux *ssystem, char *exit, void (*pa)(t_linux *))
{
	if (!exit)
		return ;
	printf("\nType\t");
	printf(""HIGHLIGHT_TEXT"%s"FONT_RESET" to exit\n\n", exit);
	while (exit)
	{
		ssystem->input = readline(ssystem->prompt);
		if (!ssystem->input || !ft_strcmp(ssystem->input, exit))
			return ((void)s_free(&ssystem->input));
		pa(ssystem);
		s_free(&ssystem->input);
	}
}
