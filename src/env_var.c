/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:59:33 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/18 06:37:08 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	cmp_for_env(char *str, char *cmp)
{
	int	i;

	i = 0;
	while (cmp[i])
		i++;
	if (i <= 1)
		return (0);
	i = 0;
	while (str[i] && cmp[i + 1])
	{
		if (str[i] != cmp[i + 1])
			return (0);
		i++;
	}
	if (str[i] && str[i] == '=')
		return (1);
	return (0);
}

char	*replace_var(t_env *env, char *str)
{
	t_env	*buf;

	buf = env;
	while (buf != NULL)
	{
		if (cmp_for_env(buf->str, str))
		{
			return (ft_strdup(ft_strchr(buf->str, '=') + 1));
		}
		buf = buf->next;
	}
	return (NULL);
}

void	change_env_arg(char **tab, t_env *env)
{
	int		i;
	char	*new;

	i = 0;
	while (tab[i])
	{
		if (ft_strchr(tab[i], '$') != NULL)
		{
			new = replace_var(env, ft_strchr(tab[i], '$'));
			if (new != NULL)
			{
				s_free(&tab[i]);
				tab[i] = new;
			}
		}
		i++;
	}
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
