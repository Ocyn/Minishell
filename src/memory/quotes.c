/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:17:33 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/22 20:44:53 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	reset_token(char	*last_token)
{
	(*last_token) = '\0';
	return (0);
}

int	pipe_repetition(char *str, char last_token, int i, int quotes)
{
	int		count;

	count = 0;
	last_token = '\0';
	while (str[++i])
	{
		quotes_check_parse(str[i], &quotes);
		if (quotes == 0)
		{
			if (ft_strchr("|", str[i]) != NULL)
			{
				if (last_token != '\0' && last_token != str[i])
					return (EXIT_FAILURE);
				last_token = str[i];
				count++;
			}
			else if (count != 0 && str[i] == ' ')
				count++;
			else
				count = reset_token(&last_token);
			if (count > 1 && ft_strchr("|", str[i]) != NULL)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	len_after_ampute(char *tab)
{
	int	i;
	int	len;
	int	quotes;

	i = 0;
	quotes = 0;
	len = 0;
	while (tab[i])
	{
		if (quotes == 0)
		{
			quotes_check_parse(tab[i], &quotes);
			if (quotes != 0)
				len--;
		}
		else
		{
			quotes_check_parse(tab[i], &quotes);
			if (quotes == 0)
				len--;
		}
		i++;
	}
	len += i;
	return (len);
}

char	*final_quotes(char *new, char *tab)
{
	int	i;
	int	j;
	int	quotes;
	int	previous;

	i = 0;
	quotes = 0;
	j = 0;
	while (tab[i + j])
	{
		previous = quotes;
		quotes_check_parse(tab[i + j], &quotes);
		while (previous != quotes && tab[i + j])
		{
			j++;
			previous = quotes;
			quotes_check_parse(tab[i + j], &quotes);
		}
		if (tab[i + j])
		{
			new[i] = tab[i + j];
			i++;
		}
	}
	return (new);
}

char	**ampute_quotes(char **tab)
{
	char	*new;
	int		i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		new = s_malloc(sizeof(char) * len_after_ampute(tab[i]) + 1);
		new = final_quotes(new, tab[i]);
		s_free(&tab[i]);
		tab[i] = new;
		i++;
	}
	return (tab);
}
