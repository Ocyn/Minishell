/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:14:41 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/20 15:56:47 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_redi(char *cmp)
{
	if (!ft_strcmp(cmp, "<") || !ft_strcmp(cmp, ">"))
		return (1);
	return (0);
}

t_lst	*token_format(t_lst *list, int *redi, char *id)
{
	int	mode;

	mode = 0;
	/* DEBUG */	printf("\t\t[%s%s%s] : ", FE_UND, ((char *)list->data), FRR);
	if (!ft_strcmp(((char *)list->data), id))
	{
		/* DEBUG */	printf("Matching == (%s)\n", id);
		list = lst_rm(list);
		mode = (list && !ft_strcmp(((char *)list->data), id));
		if (!list || (!list->next && is_redi((char *)list->data)))
			return ((void)printf("\nERROR 1\n"), list);	// Erreur de token -> annulation execve
		if (list && !ft_strcmp(((char *)list->data), id))
			list = lst_rm(list);
		if (list && ft_strcmp(((char *)list->data), id) && !is_redi((char *)list->data))
		{
			if (!ft_strcmp(id, "<"))
				redi[0] = set_infile((char *)list->data, mode, redi[0]);
			if (!ft_strcmp(id, ">"))
				redi[1] = set_outfile((char *)list->data, mode, redi[1]);
			list = list->prev;
			lst_rm(list->next);
			printf("\n\t\tCell %d after the prev one has been removed\n", list->id);
		}
	}
	return (list);
}

t_lst	*get_redirection(t_lst *list, int *redi, int *err)
{
	char	*token_type;

	token_type = 0;
	if (!list || !is_redi(((char *)list->data)))
		return (list);
	token_type = ft_strdup((char *)list->data);
	printf("\n\tGet_Redirection at Cell %d\n", list->id);
	list = token_format(list, redi, token_type);
	if (!list)
		err++;
	s_free(&token_type);
	return (list);
}

int	set_infile(char *file, int heredoc, int oldfd)
{
	int	fd;

	fd = 0;
	(void)heredoc;
	if (!file)
		return (oldfd);
	/*DEBUG*/	printf("\t\tInfile to open : [%s] | Heredoc : [%d]\n", file, heredoc);
	if (access(file, F_OK) != -1 && access(file, R_OK) != -1)
		fd = open(file, O_RDONLY);
	if (oldfd > 1)
	{
		if (fd > 1)
			close(oldfd);
		else
			fd = oldfd;
	}
	return (fd);
}

int	set_outfile(char *file, int append, int oldfd)
{
	int	fd;

	fd = 0;
	if (!file)
		return (oldfd);
	/*DEBUG*/	printf("\t\tOutfile to open : [%s] | Append : [%d]\n", file, append);
	if (append)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00700);
	else
		fd = open(file, O_CREAT | O_WRONLY, 00700);
	if (fd > 1 && oldfd > 1)
		close(oldfd);
	if (fd < 1 && oldfd > 1)
		fd = oldfd;
	return (fd);
}
