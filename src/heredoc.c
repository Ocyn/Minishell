/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 05:47:51 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/23 11:19:47 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_expand(char **list)
{
	int		quotes;
	int		ret;
	int		i;
	char	*new;

	quotes = 0;
	ret = 1;
	i = 0;
	while ((*list)[i])
	{
		quotes_check_parse((*list)[i], &quotes);
		if (quotes != 0)
			ret = 0;
		i++;
	}
	new = s_malloc(sizeof(char) * len_after_ampute((*list)) + 1);
	if (!new)
		return (ret);
	new = final_quotes(new, (*list));
	s_free(list);
	(*list) = new;
	return (ret);
}

t_lst	*heredoc_readline(char *exit, int expand, t_env *env, t_lst *lst)
{
	t_lst	*line;

	line = lst_init();
	lst = line;
	line->data = readline(">");
	if (!line->data)
		return (lst_free_list(line));
	if (!ft_strcmp(line->data, exit))
		return (lst);
	if (check_unclosed_quotes(line->data))
		return (err_custom(1, "quote error", 1), s_free(&line->data), lst);
	if (expand)
		change_env_arg((char **)&line->data, env);
	while (exit && ft_strcmp(line->data, exit))
	{
		line = lst_add(line);
		line->data = readline(">");
		if (!line->data)
			return (lst_free_list(line));
		if (check_unclosed_quotes(line->data))
			return (err_custom(1, "quote error", 1), s_free(&line->data), lst);
		if (expand)
			change_env_arg((char **)&line->data, env);
	}
	return (lst);
}

void	set_temp_file(int fd, t_lst *list)
{
	dup2(fd, STDOUT_FILENO);
	close (fd);
	if (!list)
		return ;
	while (list->next)
	{
		printf("%s\n", list->data);
		list = list->next;
		if (!list)
			break ;
	}
}

void	free_heredoc(t_lst *delim, t_lst *list, t_linux *env)
{
	s_free(&env->last_token);
	lst_free_list(list);
	lst_free_list(delim);
	close(STDOUT_FILENO);
	exit_forkfailure(-1, env, NULL);
}

int	heredocument(t_lst *delim, int expand, t_linux *env)
{
	t_lst	*list;
	int		fd;
	pid_t	fk;

	fk = 0;
	fd = -1;
	list = NULL;
	fd = open("hdtemp", O_CREAT | O_WRONLY | O_TRUNC, 00007);
	fk = fork();
	if (fk == -1)
		return (-1);
	if (fk == 0)
	{
		if (delim->data)
		{
			list = heredoc_readline(delim->data, expand, env->env, NULL);
			set_temp_file(fd, list);
		}
		free_heredoc(delim, list, env);
		exit (0);
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	fd = open("hdtemp", O_RDONLY);
	return (fd);
}
