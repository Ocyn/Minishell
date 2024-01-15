/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:27:44 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/15 15:02:13 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int		weird_cmp(char *str, char *cmp)
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

void	ft_unset(t_linux *shell, char *src)
{
	t_env	*buf;
	int		i;
	char	*str;
	t_env	*prev;

	i = 0;
	prev = NULL;
	if (src == NULL)
	{
		printf ("hey\n");
		return ;
	}
	buf = shell->env;
	str = shell->command->command.prefixes[0];
	while (buf != NULL && i == 0 && str != NULL)
	{
		if (weird_cmp(buf->str, str) == 1)
		{
			if (!prev)
			{
				shell->env = shell->env->next;
				free(buf->str);
				free(buf);
			}
			else
			{
				prev->next = buf->next;
				free(buf->str);
				free(buf);
			}
			i = 1;
		}
		else
		{
			prev = buf;
			buf = buf->next;
		}
	}
	free(str);
}

//va falloir mettre a la norme et le changer de maniere a ce que ca le fasse bien dans l'env
//et faire en sorte que ca unset chaque argument passer%  