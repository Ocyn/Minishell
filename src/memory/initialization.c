/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:21:26 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/21 14:31:24 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	change_ret_signal(int c)
{
	if (WIFEXITED(c))
		g_sign = WEXITSTATUS(c);
	else if (WIFSIGNALED(c))
	{
		if (WTERMSIG(c) == SIGQUIT)
			g_sign = 131;
		if (WTERMSIG(c) == SIGINT)
			g_sign = 130;
	}
}

void	change_oldpwd(t_linux *shell)
{
	if (shell->oldpwd)
		s_free(&shell->oldpwd);
	shell->oldpwd = getcwd(NULL, 0);
}

void	cmd_init(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->id = 0;
	cmd->meta.raw = NULL;
	cmd->meta.sraw = NULL;
	cmd->meta.exec_cmd = NULL;
	cmd->meta.infile = -1;
	cmd->meta.outfile = -1;
}

void	init_struct(t_linux *shell)
{
	shell->head = s_malloc(sizeof(t_cmd));
	if (!shell->head)
		return ;
	cmd_init(shell->head);
	g_sign = 0;
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

void	basic_env(t_env *env)
{
	t_env	*buf;
	char	*str;

	buf = env;
	str = get_var(env, "SHLVL");
	if (!str)
	{
		if (!buf->str)
		{
			buf->str = put_in("SHLVL=1");
			return ;
		}
		while (buf != NULL)
			buf = buf->next;
		buf = malloc(sizeof(t_env));
		if (!buf->next)
			return ;
		buf = buf->next;
		buf->next = NULL;
		buf->str = put_in("SHLVL=1");
	}
	else
		s_free(&str);
}
