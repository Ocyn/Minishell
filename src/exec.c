/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:10:31 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 01:37:45 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_path(char *command, char **env)
{
	char	*cmd_path;
	char	*check;
	char	**var;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp(env[i], "PATH=", 5) != 0)
		return (NULL);
	cmd_path = ft_strtrim(env[i], "PATH=");
	var = ft_split(cmd_path, ':');
	s_free((void *)cmd_path);
	i = 0;
	check = ft_strjoin("/", command);
	while (var[i])
	{
		cmd_path = ft_strjoin(var[i], check);
		if (access(cmd_path, F_OK))
			break ;
		s_free((void *)cmd_path);
		i++;
	}
	return (s_free((void *)check), cmd_path);
}

// void	bin_command(t_linux *shell)
// {
// 	t_execv	cmd;

// 	cmd.path = get_path(&cmd, shell->envi);
// 	if (!cmd.cmd)
// 		return ;
// 	cmd.f_id = fork();
// 	if (cmd.f_id == -1)
// 	{
// 		perror("fork failed");
// 		free(cmd.cmd);
// 		return ;
// 	}
// 	if (cmd.f_id == 0)
// 	{
// 		args = ft_split(shell->history[shell->nb_history - 1], ' ');
// 		if (!args)
// 			return ;
// 		execv(cmd, args);
// 		perror("execv failed");
// 		free(cmd);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 		waitpid(cmd.f_id, &status, 0);
// 	free(cmd);
// }
