/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:14:41 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/23 11:09:12 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_redi(char *cmp)
{
	if (!ft_strcmp(cmp, "<") || !ft_strcmp(cmp, ">"))
		return (1);
	return (0);
}

t_lst	*token_format(t_lst *list, int *redi, char *id, t_linux *env)
{
	int	mode;

	mode = 0;
	if (!ft_strcmp(list->data, id))
	{
		list = lst_rm(list);
		mode = (list && !ft_strcmp(list->data, id));
		if (!list || (!list->next && is_redi(list->data)))
		{
			redi[2] = 1;
			return (err_parse_token(1), lst_rm(list));
		}
		if (list && !ft_strcmp(list->data, id))
			list = lst_rm(list);
		if (list && ft_strcmp(list->data, id) && !is_redi(list->data))
		{
			if (!ft_strcmp(id, "<"))
				redi[0] = set_infile(list, mode, redi[0], env);
			if (!ft_strcmp(id, ">"))
				redi[1] = set_outfile(list->data, mode, redi[1]);
			list = list->prev;
			lst_rm(list->next);
		}
	}
	return (list);
}

t_lst	*get_redirection(t_lst *list, int *redi, t_linux *env)
{
	env->last_token = NULL;
	if (!list || !is_redi(list->data))
		return (list);
	env->last_token = ft_strdup(list->data);
	list = token_format(list, redi, env->last_token, env);
	s_free(&env->last_token);
	env->last_token = NULL;
	return (list);
}

int	set_infile(t_lst *file, int heredoc, int oldfd, t_linux *env)
{
	int	fd;

	fd = 0;
	if (!file->data)
		return (oldfd);
	if (heredoc)
		fd = heredocument(file, is_expand(&file->data), env);
	else if (access(file->data, F_OK) \
	!= -1 && access(file->data, R_OK) != -1)
		fd = open(file->data, O_RDONLY);
	err_perror((fd <= 2));
	if (oldfd > 2)
	{
		if (fd > 2)
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
	if (append)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd > 1 && oldfd > 1)
		close(oldfd);
	if (fd < 1 && oldfd > 1)
		fd = oldfd;
	return (fd);
}
