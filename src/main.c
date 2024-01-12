/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:32 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/12 14:17:18 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_linux		shell;

	(void)argc;
	(void)argv;
	//return (db_debug(), 0);
	shell.input = NULL;
	struct_init(&shell);
	create_signal(ctrl_c, ctrl_slash);
	shell.envi = env;
	shell.prompt = prompt_tuning("[Minishell |", "#", "FC_PUR BN_GRA FE_BOL");
	read_prompt(&shell, "exit", parse);
	s_free(&shell.prompt);
	s_free(&shell.oldpwd);
	rl_clear_history();
	free(shell.head);
	return (0);
}

void	struct_init(t_linux *shell)
{
	shell->head = s_malloc(sizeof(t_cmd));
	if (!shell->head)
		return ;
	cmd_init(shell->head);
	shell->oldpwd = NULL;
	shell->prompt = NULL;
	shell->head->next = NULL;
	shell->head->prev = NULL;
	shell->head->id = 0;
	shell->envi = NULL;
	shell->end = 0;
	shell->count_cmd = 0;
	shell->token = NULL;
	shell->command = shell->head;
	change_oldpwd(shell);
}
