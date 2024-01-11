/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:41:56 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/11 14:53:19 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ctrl_c(int sig, siginfo_t *inf, void *gain)
{
	write(1,"\n",1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)gain;
	(void)inf;
	(void)sig;
}

void	ctrl_slash(int sig, siginfo_t *inf, void *gain)
{
	nothing(sig, inf, gain);
}

void	nothing(int sig, siginfo_t *inf, void *gain)
{
	(void)gain;
	(void)inf;
	(void)sig;
}

void	create_signal(void *c, void *sla)
{
	struct sigaction	sa;
	struct sigaction	slash;

	sigemptyset(&sa.sa_mask);
	sigemptyset(&slash.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = c;
	slash.sa_flags = SA_SIGINFO;
	slash.sa_sigaction = sla;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &slash, 0);
}
