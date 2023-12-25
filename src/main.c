/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:32 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 06:44:31 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_linux	shell;
	char	*input;

	input = NULL;
	struct_init(&shell, argc, argv, env);
	//return (db_debug(&shell, shell.envi, NULL), 0);
	while (!shell.end)
	{
		input = readline("minishell>>");
		parse(input, &shell);
		s_free(&input);
	}
	rl_clear_history();
	return (0);
}
