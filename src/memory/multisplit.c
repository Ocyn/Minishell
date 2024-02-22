/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multisplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:47:35 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/20 20:51:53 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	**initialization(int *i, int *t, int *quote, char **tab);
static char	**tab_init(const char *s, char *keys);
static int	quote_checking(int *quote);
static void	quote_setting(int *quote, char check);

char	**multisplit(const char *s, char *keys)
{
	char		**tab;
	int			quote[3];
	int			t;
	int			len;
	int			i;

	tab = initialization(&i, &t, quote, tab_init(s, keys));
	while (tab && ++i < (int)ft_strlen(s))
	{
		len = -1;
		while (s[i] && ++len > -1 && s[i + len] \
		&& (!ft_strchr(keys, s[i + len]) || quote_checking(quote)))
			quote_setting(quote, s[i + len]);
		if (len > 0)
		{
			tab[++t] = ft_substr(s, i, len);
			if (!tab[t])
				return (free_tab(tab, t), NULL);
			i += len;
		}
	}
	return (tab);
}

static void	quote_setting(int *quote, char check)
{
	int	doubleq;
	int	prev;

	prev = quote[1] % 2;
	quote[0] += (check == '\'');
	quote[1] += (check == '\"');
	doubleq = quote[1] % 2;
	if (doubleq && !prev)
		quote[2] = 1;
	else if (!doubleq && prev)
		quote[2] = -1;
	else
		quote[2] = 0;
	if (quote[2] == -1)
		quote[0] = 2;
}

static char	**initialization(int *i, int *t, int *quote, char **tab)
{
	*i = -1;
	*t = -1;
	quote[0] = 0;
	quote[1] = 0;
	quote[2] = 0;
	return (tab);
}

static char	**tab_init(const char *s, char *key)
{
	char	**init;
	int		quote[2];
	int		cmd;
	int		i;

	init = NULL;
	i = -1;
	quote[0] = 0;
	quote[1] = 0;
	cmd = 1;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		quote[0] += (s[i] == '\'');
		quote[1] += (s[i] == '\"');
		cmd += (ft_strchr(key, s[i]) && s[i + 1] && !ft_strchr(key, s[i + 1]));
	}
	cmd += (quote[0] / 2);
	cmd += (quote[1] / 2);
	init = s_malloc(sizeof(char *) * (cmd + 1));
	if (!init)
		return (NULL);
	init[cmd] = NULL;
	return (init);
}

static int	quote_checking(int *quote)
{
	int	simpleq;
	int	doubleq;
	int	changed_state;

	simpleq = quote[0] % 2;
	doubleq = quote[1] % 2;
	changed_state = quote[2];
	(void)changed_state;
	if (doubleq)
		return (1);
	if (!simpleq || changed_state == -1)
		return (0);
	return (1);
}
