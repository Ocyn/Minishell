/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:32 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/21 22:51:38 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_linux	shell;
	char	*input;

	(void)argv;
	(void)argc;
	struct_init(&shell, argc, argv, env);
	return (db_debug(&shell, shell.envi, NULL), 0);
	while (!shell.end)
	{
		input = readline("minishell>>");
		parse(input, &shell);
		if (!is_builtin(&shell))
			bin_command(&shell);
		free(input);
		free(shell.command);
	}
	free_all(&shell);
	return (0);
}
