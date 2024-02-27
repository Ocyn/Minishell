/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 03:44:24 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/22 17:35:01 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "../header/define_syntax.h"

void	read_prompt(t_linux *ssystem, char *exit, void (*pa)(t_linux *))
{
	if (!exit)
		return ;
	while (ssystem->end != 1 && exit)
	{
		ssystem->input = readline(ssystem->prompt);
		if (!ssystem->input || !ft_strcmp(ssystem->input, exit))
			return ((void)s_free(&ssystem->input));
		pa(ssystem);
		s_free(&ssystem->input);
	}
}
