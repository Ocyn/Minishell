/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:26:48 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/17 23:35:59 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_in_env(char *str, t_env *env)
{
	t_env	*buf;

	buf = env;
	while (buf != NULL)
	{
		if (weird_cmp_export(buf->str, str))
			return (1);
		buf = buf->next;
	}
	return (0);
}

int	error(char *str)
{
	printf ("they are a problem with the syntax of : %s\n", str);
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
		if (arguments[j] == '=')
			count++;
		if (is_space(arguments[j]))
			return (error(arguments));
		j++;
	}
	if (count == 0)
		return (error(arguments));
	return (nicely_done(arguments));
}

void	ft_export(t_linux *shell)
{
	t_env	*buf;
	int		i;

	i = 0;
	g_sign = 0;
	while (shell->head->next->meta.raw[++i])
	{
		if (test_valid(shell->head->next->meta.raw[i]))
		{
			if (is_in_env(shell->head->next->meta.raw[i], shell->env))
				ft_unset(shell, shell->head->next->meta.raw[i]);
			else
			{
				buf = shell->env;
				while (buf->next)
					buf = buf->next;
				buf->next = malloc(sizeof(t_env));
				if (!buf->next)
					return ;
				buf = buf->next;
				buf->next = NULL;
				buf->str = put_in(shell->head->next->meta.raw[i]);
			}
		}
	}
}
