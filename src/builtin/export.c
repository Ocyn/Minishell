/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:26:48 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/16 15:25:35 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	error(char *str)
{
	printf ("they are a problem with the syntax of : %s\n", str);
	return (0);
}

int	test_valid(char *arguments)
{
	int	j;
	int	count;
	
	j = 0;
	count = 0;
	while (arguments[j])
	{
		if (j == 0 && arguments[j] == '=')
			return (error(arguments));
		if (arguments[j] == '=')
			count++;
		if (j != 0 &&is_space(arguments[j - 1]) && arguments[j] == '=' && count == 1)
			return (error(arguments));
		
		j++;
	}
	if (count == 0)
		return (error(arguments));
	return (1);
}

void	ft_export(t_linux *shell)
{
	t_env	*buf;
	int		i;
 
	i = 1;
	buf = shell->env;
	while(buf->next)
		buf = buf->next;
	while (shell->head->next->command.prefixes[i])
	{
		if (test_valid(shell->head->next->command.prefixes[i]))
		{
			ft_unset(shell, shell->head->next->command.prefixes[i]);
			buf->next = malloc(sizeof(t_env));
			if (!buf->next)
				return ;
			buf = buf->next;
			buf->next = NULL;
			buf->str = put_in(shell->head->next->command.prefixes[i]);
		}
		i++;
	}
}

//changement a faire : phrase du avant egal a mieux parser (_, pas de digit en first)
//changement a faire : enlever les guillemets durant le parsing je pense, tel "salut= ca va" en salut= ca va
//changement a faire : oui, les guillmets aussi genre salut="cava", donne salut=cava
