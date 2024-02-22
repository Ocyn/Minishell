/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:27:44 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/22 19:25:23 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	weird_cmp_export(char *str, char *cmp)
{
	int	i;

	i = 0;
	while (str[i] && cmp[i] && cmp[i] != '=')
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	if (str[i] && str[i] == '=')
		return (1);
	return (0);
}

int	weird_cmp(char *str, char *cmp)
{
	int	i;

	i = 0;
	while (str[i] && cmp[i])
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	if (str[i] && str[i] == '=')
		return (1);
	return (0);
}

void	unset_cmd(t_cmd *cmd, t_env *buff, t_env *env, t_env *prev)
{
	int	i;

	while (buff != NULL)
	{
		i = 0;
		while (cmd->meta.raw[++i])
		{
			if (weird_cmp(buff->str, cmd->meta.raw[i]) && !prev)
			{
				env = env->next;
				total_free(buff);
				buff = env;
			}
			else if (weird_cmp(buff->str, cmd->meta.raw[i]))
			{
				prev->next = buff->next;
				total_free(buff);
				buff = prev;
			}
		}
		prev = buff;
		buff = buff->next;
	}
}

void	unset_export(t_env *env, char *str)
{
	t_env	*buff;

	buff = env;
	while (buff != NULL)
	{
		if (weird_cmp_export(buff->str, str))
		{
			free(buff->str);
			buff->str = put_in(str);
		}
		buff = buff->next;
	}
}

void	ft_unset(t_cmd *cmd, t_env *env, char *str)
{
	int	i;

	if (str != NULL)
		unset_export(env, str);
	else
	{
		i = 0;
		while (cmd->meta.raw[i])
			i++;
		if (i > 1)
		{
			unset_cmd(cmd, NULL, env, NULL);
			g_sign = 0;
		}
		else
			g_sign = 1;
	}
}
