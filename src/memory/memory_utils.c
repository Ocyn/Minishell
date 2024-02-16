/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 08:14:08 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/14 14:27:18 by jcuzin           ###   ########.fr       */
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
	/*DEBUG*/	//db_tabstr_display(raw, "\n\t\tTabDup", token_len);
	return (raw);
}

