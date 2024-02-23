/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 05:47:51 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/23 00:15:07 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_lst	*heredoc_readline(char *exit, int expand, t_env *env)
{
	t_lst	*line;

	line = NULL;
	if (!exit)
		return (NULL);
	while (exit)
	{
		line = lst_add(line);
		line->data = readline(">");
		if (!line->data)
			return (lst_free_list(line));
		if (!ft_strcmp(line->data, exit))
			break ;
		if (expand)
			change_env_arg((char **)&line->data, env);
	}
	return (line);
}

int	set_temp_file(char *filename, t_lst *list)
{
	int	fd;

	fd = -1;
	dup2(fd, STDOUT_FILENO);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 00700);
	if (!list || err_perror((fd == -1)))
		return (-1);
	while (fd != -1 && list)
	{
		printf("%s\n", list->data);
		list = list->next;
		if (!list)
			break ;
	}
	return (fd);
}

int	heredocument(char *delim, int expand, t_env *env)
{
	t_lst	*list;
	int		outp[2];
	int		fd;
	pid_t	fk;

	fk = 0;
	fd = -1;
	list = NULL;
	if (err_perror(pipe_tool(outp, 1)))
		return (-1);
	fk = fork();
	if (fk == -1)
		return (-1);
	if (fk == 0)
	{
		close(outp[0]);
		list = heredoc_readline(delim, expand, env);
		fd = set_temp_file(".hdtemp", list);
		pipe_tool(outp, 0);
		free_env(env);
		exit(g_sign);
	}
	err_perror(pipe_tool(outp, 0));
	return (fd);
}
