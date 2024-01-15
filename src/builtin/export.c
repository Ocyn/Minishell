/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:26:48 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/15 17:05:02 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	error(char *str)
{
	printf ("they are a problem with the syntax of : %s\n", str);
	return (0);
}

int	test_valid(char **arguments)
{
	int	i;
	int	j;
	int	count;
	
	i = 1;
	while (arguments[i])
	{
		j = 0;
		count = 0;
		while (arguments[i][j])
		{
			if (j == 0 && arguments[i][j] == '=')
				return (error(arguments[i]));
			if (arguments[i][j] == '=')
				count++;
			if (is_space(arguments[i][j - 1]) && arguments[i][j] == '=' && count == 1)
				return (error(arguments[i]));
			
			j++;
		}
		if (count == 0)
			return (error(arguments[i]));
		i++;
	}
	return (1);
}

void	ft_export(t_linux *shell)
{
	t_env	*buf;
	int		i;
 
	i = 1;
	if (test_valid(shell->head->next->command.prefixes) == 0)
		return ;
	buf = shell->env;
	while(buf->next)
		buf = buf->next;
	while (shell->head->next->command.prefixes[i])
	{
		buf->next = malloc(sizeof(t_env));
		if (!buf->next)
			return ;
		buf = buf->next;
		buf->next = NULL;
		//ft_unset(shell, str);
		buf->str = put_in(shell->head->next->command.prefixes[i]);
		i++;
	}
}

//alors, si y a plusiuer argument, et que parmis eux y a juste des truc sans egal, a cote de format valide
//on ajoute ce truc avec un truc vide
//genre export salut hey=fd, on export les deux et "salut="
//il faut aussi gerer car dans le parsing, j'ai plus les nombre
