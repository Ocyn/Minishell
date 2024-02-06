/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:06:46 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/30 18:47:37 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_var(t_env *env, char *str)
{
	t_env	*buf;

	buf = env;
	while (buf != NULL)
	{
		if (weird_cmp(buf->str, str))
			return (ft_strdup(ft_strchr(buf->str, '=') + 1));
		buf = buf->next;
	}
	return (put_in(NULL));
}

void	change_env(t_linux *shell, char **env)
{
	t_env	*current;
	int		i;

	i = 0;
	shell->env = malloc(sizeof(t_env));
	if (!shell->env)
		return ;
	shell->env->next = NULL;
	if (env[i])
		shell->env->str = put_in(env[i]);
	else
	{
		shell->env->str = put_in(NULL);
		return ;
	}
	current = shell->env;
	while (env[++i])
	{
		current->next = malloc(sizeof(t_env));
		if (!current->next)
			return ;
		current = current->next;
		current->str = put_in(env[i]);
		current->next = NULL;
	}
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*buf;
	t_env	*next;

	buf = env;
	while (buf)
	{
		next = buf->next;
		total_free(buf);
		buf = next;
	}
}

void	total_free(t_env *chain)
{
	s_free(&chain->str);
	free(chain);
}