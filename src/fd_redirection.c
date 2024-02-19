/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:14:41 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/19 05:21:59 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_type(char cmp)
{
	if (cmp == '<' || cmp == '>')
		return (1);
	return (0);
}

t_lst	*token_format(t_lst *list, int *redi, int type)
{
	int	rep;
	int	mode;

	mode = 0;
	rep = 0;
	if (type == _TOK_HEREDOC || type == _TOK_OUTFILE_APP)
		mode = 1;
	while (check_type(((char *)list->data)[0]))
	{
		list = lst_rm(list);
		if (++rep > 2)
			return (lst_free_list(list));
	}
	if ((type == _TOK_HEREDOC || type == _TOK_INFILE))
		redi[0] = set_infile((char *)list->data, mode);
	if ((type == _TOK_OUTFILE || type == _TOK_OUTFILE_APP))
		redi[1] = set_outfile((char *)list->data, mode);
	if (list->next)
		list = list->next;
	return (list);
}

int	set_infile(char *file, int heredoc)
{
	int	fd;

	fd = 0;
	(void)heredoc;
	if (!file)
		return (-1);
	/*DEBUG*/	printf("\t\tinfile to open : [%s]\n", file);
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
	/*DEBUG*/	printf("\t\toutfile to open : [%s]\n", file);
	if (overwrite)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00700);
	else
		fd = open(file, O_CREAT | O_WRONLY, 00700);
	if (!fd || !access(file, F_OK) || !access(file, W_OK))
		return (-1);
	return (fd);
}
