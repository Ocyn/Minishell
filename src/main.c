/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:32 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/29 04:10:07 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_linux		shell;

	shell.input = NULL;
	struct_init(&shell, argc, argv, env);
	//return (db_debug(&shell), 0);
	while (!shell.end)
	{
		shell.input = readline("minishell>>");
		parse(shell.input, &shell);
		s_free(&shell.input);
	}
	rl_clear_history();
	//free(shell.head->next);
	free(shell.head);
	return (0);
}

void	struct_init(t_linux *shell, int a_nb, char **a_s, char **genv)
{
	(void)a_nb;
	(void)a_s;
	ft_bzero(shell, sizeof(t_linux));
	shell->head = malloc(sizeof(t_cmd));
	if (!shell->head)
		return ;
	cmd_init(shell->head, NULL, 0);
	shell->head->next = NULL;
	shell->head->prev = NULL;
	shell->head->id = 0;
	shell->envi = NULL;
	shell->nb_history = 0;
	shell->history = NULL;
	shell->end = 0;
	shell->envi = genv;
	shell->count_cmd = 0;
}
