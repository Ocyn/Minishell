/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:59:33 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/18 09:49:27 by jcuzin           ###   ########.fr       */
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
			return (ft_strdup(ft_strchr(buf->str, '=') + 1));
		buf = buf->next;
	}
	return (NULL);
}

char	*expended_variable(char *tab, char *str, int j)
{
	char	*buf;
	int		i;

	i = 0;
	j = 0;
	while (tab[j] != '$')
		j++;
	buf = malloc(sizeof(char) * (j + ft_strlen(str) + 1));
	if (!buf)
		return (NULL);
	while (i < j)
	{
		buf[i] = tab[i];
		i++;
	}
	if (str != NULL)
	{
		while (i < (int)(j + ft_strlen(str)))
		{
			buf[i] = str[i - j];
			i++;
		}
	}
	buf[i] = '\0';
	return (buf);
}

void	change_env_arg(char **tab, t_env *env)
{
	int		i;
	char	*new;
	char	*buf;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "$") &&\
			ft_strcmp(tab[i], "$?") && ft_strchr(tab[i], '$') != NULL)
		{
			new = replace_var(env, ft_strchr(tab[i], '$'));
			buf = expended_variable(tab[i], new, 0);
			if (buf != NULL)
			{
				s_free(&tab[i]);
				tab[i] = buf;
			}
			if (new)
				s_free(&new);
		}
		i++;
	}
}
