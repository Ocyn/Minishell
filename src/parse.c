/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/21 22:55:23 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	history_add(char *str, t_linux *shell)
{
	int		i;
	char	**hist;

	shell->nb_history++;
	hist = malloc(sizeof(char *) * (shell->nb_history + 1));
	if (!hist)
		return ;
	i = 0;
	while (i < shell->nb_history - 1)
	{
		hist[i] = put_in(shell->history[i]);
		free(shell->history[i]);
		i++;
	}
	hist[i] = put_in(str);
	hist[i + 1] = 0;
	if (shell->nb_history != 1)
		free(shell->history);
	shell->history = hist;
}

void	parse(char *str, t_linux *shell)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i] && str[i] != ' ')
		j++;
	shell->command = malloc(sizeof(char) * i + 1);
	if (!shell->command)
		return ;
	i = -1;
	while (str[++i] && str[i] != ' ')
		shell->command[i] = str[i];
	shell->command[i] = '\0';
	history_add(str, shell);
}

void	struct_init(t_linux *shell, int a_nb, char **a_s, char **genv)
{
	(void)a_nb;
	(void)a_s;
	shell->envi = NULL;
	shell->command = 0;
	shell->nb_history = 0;
	shell->history = NULL;
	shell->end = 0;
	shell->envi = genv;
}
