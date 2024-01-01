/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:32 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/01 12:42:37 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_linux		shell;
	char		*prompt;

	shell.input = NULL;
	prompt = NULL;
	struct_init(&shell, argc, argv, env);
	prompt = prompt_tuning("[Minishell |", "#", "FC_PUR BN_GRA FE_BOL");
	//return (db_debug(&shell), 0);
	while (!shell.end)
	{
		shell.input = readline(prompt);
		parse(shell.input, &shell);
		s_free(&shell.input);
	}
	s_free(&prompt);
	rl_clear_history();
	free(shell.head);
	return (0);
}

void	struct_init(t_linux *shell, int a_nb, char **a_s, char **genv)
{
	(void)a_nb;
	(void)a_s;
	ft_bzero(shell, sizeof(t_linux));
	shell->head = s_malloc(sizeof(t_cmd));
	if (!shell->head)
		return ;
	cmd_init(shell->head, NULL, 0);
	shell->head->next = NULL;
	shell->head->prev = NULL;
	shell->head->id = 0;
	shell->envi = NULL;
	shell->end = 0;
	shell->envi = genv;
	shell->count_cmd = 0;
}
