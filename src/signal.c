/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:41:56 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/22 14:10:58 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ctrl_c(int sig, siginfo_t *inf, void *gain)
{
	write (2, "\n", 1);
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
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (NULL);
}
