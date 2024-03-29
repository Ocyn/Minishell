/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:26:48 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/23 12:18:29 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_in_env(char *str, t_env *env)
{
	t_env	*buf;

	buf = env;
	while (buf)
	{
		if (buf->str && weird_cmp_export(buf->str, str))
			return (1);
		if (!buf->next)
			buf->next = NULL;
		buf = buf->next;
	}
	return (0);
}

int	error(char *str)
{
	ft_putstr_fd ("they are a problem with the syntax of : ", 2);
	ft_putstr_fd (str, 2);
	ft_putstr_fd ("\n", 2);
	g_sign = 1;
	return (0);
}

int	nicely_done(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (error(str));
	i++;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (error(str));
		i++;
	}
	return (1);
}

int	test_valid(char *arguments)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (arguments[j] && count == 0)
	{
		if (j == 0 && arguments[j] == '=')
			return (error(arguments));
		if (is_space(arguments[j]))
			return (error(arguments));
		j++;
	}
	return (nicely_done(arguments));
}

void	ft_export(t_cmd *cmd, t_env *env)
{
	t_env	*buf;
	int		i;

	i = 0;
	g_sign = 0;
	while (cmd->meta.exec_cmd[++i])
	{
		if (test_valid(cmd->meta.exec_cmd[i]))
		{
			if (is_in_env(cmd->meta.exec_cmd[i], env))
				ft_unset(cmd, env, cmd->meta.exec_cmd[i]);
			else
			{
				buf = env;
				while (buf && buf->next)
					buf = buf->next;
				buf->next = malloc(sizeof(t_env));
				if (!buf->next)
					return ;
				buf = buf->next;
				buf->next = NULL;
				buf->str = put_in(cmd->meta.exec_cmd[i]);
			}
		}
	}
}
