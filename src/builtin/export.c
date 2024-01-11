/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:26:48 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/11 16:48:10 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
/*
char	*modified(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (str[i] && is_space(str[i]) == 0)
		i++;
	new = malloc(sizeof(char) * i + 1);
	if (!new)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*cut_export(char *str)
{
	char	*path;
	int		i;
	int		j;

	i = 7;
	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i + j])
		j++;
	if (j > 0)
	{
		path = malloc (sizeof(char) * j + 1);
		if (!path)
			return (NULL);
		j = 0;
		while (str[i + j])
		{
			path[j] = str[i + j];
			j++;
		}
		path[j] = '\0';
		return (path);
	}
	return (NULL);
}

int	is_export(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '=' && i > 0 && is_space(str[i - 1]) == 0)
			ret = 1;
		else if (str[i] == '=')
			return (0);
		i++;
	}
	return (ret);
}

void	ft_export(t_linux *shell)
{
	t_env	*buf;
	char	*str;

	buf = shell->env;
	str = cut_export(shell->history[shell->nb_history - 1]);
	if (!str)
		return ;
	if (is_export(str) == 0)
		return ;
	//ft_unset(shell, str);
	while(buf->next)
		buf = buf->next;
	buf->next = malloc(sizeof(t_env));
	if (!buf->next)
		return ;
	buf = buf->next;
	buf->next = NULL;
	buf->str = modified(str);
	free(str);
}

//changement a faire : on prend chaque fois qu'on a un egal, et on print tout ce qu'il a de colle a celui ci
//si il ny a rien avant l'egal, on ne fait rien
//et ceux pour tout les arguments
//et bien sur avant, on unset ce qui y a avant egal, avant de l'export
*/

void	ft_export(t_linux *shell)
{
	(void)shell;
	
	printf ("gl hf q moi \n");
}//changement a faire : on prend chaque fois qu'on a un egal, et on print tout ce qu'il a de colle a celui ci
//si il ny a rien avant l'egal, on ne fait rien
//et ceux pour tout les arguments
//et bien sur avant, on unset ce qui y a avant egal, avant de l'export