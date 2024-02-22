/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:41:56 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/22 11:55:17 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ctrl_c(int sig, siginfo_t *inf, void *gain)
{
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sign = 130;
	(void)gain;
	(void)inf;
	(void)sig;
}

void	nothing(int sig, siginfo_t *inf, void *gain)
{
	if (sig == SIGQUIT)
	{
		g_sign = 131;
		printf ("Quit (core dumped)\n");
	}
	if (sig == SIGINT)
		g_sign = 130;
	(void)gain;
	(void)inf;
	(void)sig;
}

void	create_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ctrl_c;
	sigaction(SIGINT, &sa, 0);
	signal(SIGQUIT, SIG_IGN);
}

void	let_signal_through(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = nothing;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}

char	*path_not_found(char *str)
{
	if (!access(str, F_OK))
		return (ft_strdup(str));
	printf ("%s: command not found\n", str);
	return (NULL);
}
