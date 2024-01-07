/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 08:14:08 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 08:18:37 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**tab_dup(char **token_tab, int token_len)
{
	char	**raw;
	int		i;

	i = -1;
	raw = NULL;
	raw = s_malloc(sizeof(char *) * (token_len + 1));
	while (++i < token_len)
		raw[i] = ft_strdup(token_tab[i]);
	db_tabstr_display(raw, "\n\t\tTabDup", token_len);
	return (raw);
}

int	skip_until(char **tab, int (*stop)(char *, int))
{
	int	len;
	int	i;

	i = 0;
	len = tablen(tab);
	while (i < len && tab[i] && !stop(tab[i], 0))
		i++;
	i += (stop(tab[i], 0) != 0);
	return (i);
}
