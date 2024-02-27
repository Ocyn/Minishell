/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:01:32 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/23 14:18:36 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_sign;

int	main(int argc, char **argv, char **env)
{
	t_linux		shell;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd ("minishell : No such file or directory \n", 2);
		return (127);
	}
	shell.input = NULL;
	init_struct(&shell);
	create_signal();
	change_env(&shell, env);
	basic_env(shell.env);
	shell.envi = env;
	shell.prompt = prompt_tuning("[Minishell |", "#", "FC_PUR BN_GRA FE_BOL");
	read_prompt(&shell, "exit", parse);
	exit_end(1, &shell);
	return (g_sign);
}
