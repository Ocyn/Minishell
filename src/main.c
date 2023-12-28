/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:32 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/29 00:35:30 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_linux		shell;

	shell.input = NULL;
	struct_init(&shell, argc, argv, env);
	return (db_debug(&shell), 0);
	while (!shell.end)
	{
		shell.input = readline("minishell>>");
		parse(shell.input, &shell);
		s_free(&shell.input);
	}
	rl_clear_history();
	free(shell.head);
	return (0);
}
