/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:32 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 01:56:05 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_linux	shell;
	char	*input;

	input = NULL;
	struct_init(&shell, argc, argv, env);
	return (db_debug(&shell, shell.envi, NULL), 0);
	while (!shell.end)
	{
		input = readline("minishell>>");
		parse(input, &shell);
		s_free((void *)input);
	}
	rl_clear_history();
	//free_tab((void *)shell, 0);
	return (0);
}
