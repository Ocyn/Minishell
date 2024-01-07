/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:41:56 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 01:07:32 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void    ctrl_c(int  sig, siginfo_t *inf, void *gain)
{
    printf ("hey im a ctrl c \n");
    rl_replace_line("",0);
    rl_on_new_line();
    rl_redisplay();
    (void)gain;
    (void)inf;
    (void)sig;
}

void    ctrl_slash(int  sig, siginfo_t *inf, void *gain)
{
    printf ("hey im a ctrl / \n");
    (void)gain;
    (void)inf;
    (void)sig;
    exit(1);
}

void	create_signal()
{
	struct sigaction	sa;
	struct sigaction	slash;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ctrl_c;
	slash.sa_flags = SA_SIGINFO;
	slash.sa_sigaction = ctrl_slash;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &slash, 0);
}

//ctrl d c'est le caractere EOF, a gerer dans le prompt, sinon juste newline
