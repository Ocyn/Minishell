/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:06:46 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/15 14:20:37 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	change_env(t_linux *shell, char **env)
{
	int		i;
	t_env	*current;

	i = 0;
	shell->env = malloc(sizeof(t_env));
	if (!shell->env)
		return ;
	shell->env->str = put_in(env[i]);
	shell->env->next = NULL;
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
	return ;
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
