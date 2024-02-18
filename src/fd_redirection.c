/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:14:41 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/18 23:16:45 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_type(t_lst *list)
{
	if (!list)
		return (0);
	if (((char *)list->data)[0] != '>')
		return (1);
	return (0);
}

t_lst	*token_format(t_lst *list, int *redi, int type \
, int (*set_redi)(char *, int))
{
	int	mode;

	mode = 0;
	if (type == _TOK_HEREDOC || type == _TOK_OUTFILE_APP)
		mode = 1;
	if (check_type(list) == type)
	{
		list = list->next;
		lst_rm(list->prev);
		redi[0] = set_redi((char *)list->data, mode);
	}
	return (list);
}

int	set_infile(char *file, int heredoc)
{
	int	fd;

	fd = 0;
	(void)heredoc;
	if (!file)
		return (-1);
	/*DEBUG*/	printf("\n\t\tinfile to open : [%s]\n", file);
	if (!access(file, F_OK) && !access(file, R_OK))
		fd = open(file, O_RDONLY);
	if (!fd)
		return (-1);
	return (fd);
}

int	set_outfile(char *file, int overwrite)
{
	int	fd;

	fd = 0;
	if (!file)
		return (-1);
	/*DEBUG*/	printf("\n\t\toutfile to open : [%s]\n", file);
	if (overwrite)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00700);
	else
		fd = open(file, O_CREAT | O_WRONLY, 00700);
	if (!fd || !access(file, F_OK) || !access(file, W_OK))
		return (-1);
	return (fd);
}
