/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:27:44 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/06 05:58:12 by jcuzin           ###   ########.fr       */
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

void	unset_cmd(t_linux *shell, int i, t_env *buff, t_env *prev)
{
	buff = shell->env;
	while (buff != NULL)
	{
		i = 0;
		while (shell->head->next->meta.exec_cmd[++i])
		{
			if (weird_cmp(buff->str, shell->head->next->meta.exec_cmd[i]))
			{
				if (!prev)
				{
					shell->env = shell->env->next;
					total_free(buff);
					buff = shell->env;
				}
				else
				{
					prev->next = buff->next;
					total_free(buff);
					buff = prev;
				}
			}
		}
		prev = buff;
		buff = buff->next;
	}
}

void	unset_export(t_linux *shell, char *str)
{
	t_env	*buff;

	buff = shell->env;
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

void	ft_unset(t_linux *shell, char *str)
{
	int	i;

	if (str != NULL)
		unset_export(shell, str);
	else
	{
		i = 0;
		while (shell->head->next->meta.exec_cmd[i])
			i++;
		if (i > 1)
		{
			unset_cmd(shell, 0, NULL, NULL);
			g_sign = 0;
		}
		else
			g_sign = 1;
	}
}
