/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocyn <ocyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:41:56 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/26 00:51:06 by ocyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ctrl_c(int sig, siginfo_t *inf, void *gain)
{
	write(1,"\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)gain;
	(void)inf;
	(void)sig;
}

void	nothing(int sig, siginfo_t *inf, void *gain)
{
	(void)gain;
	(void)inf;
	(void)sig;
}

void	create_signal(void *c)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = c;
	sigaction(SIGINT, &sa, 0);
	signal(SIGQUIT, SIG_IGN);
}
