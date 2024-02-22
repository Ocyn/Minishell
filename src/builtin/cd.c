/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:08:13 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/22 14:14:02 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	error_cd(char *str)
{
	err_custom(1, str);
	g_sign = 1;
}

char	*search_path(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	if (i == 1)
		return (put_in("~"));
	else if (i == 2)
		return (put_in(str[1]));
	else
		return (NULL);
}

void	change_to_home(t_linux	*shell)
{
	char	*home;
	char	*pwd;

	home = get_var(shell->env, "HOME");
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		if (home != NULL)
		{
			if (chdir(home) != 0)
				error_cd("cd: HOME not set");
			else
			{
				if (shell->oldpwd)
					s_free(&shell->oldpwd);
				shell->oldpwd = put_in(pwd);
				g_sign = 0;
			}
			s_free(&home);
		}
		free(pwd);
	}
}

char	*what_path(t_linux	*shell, char **str)
{
	char	*oldpwd;
	char	*path;

	path = search_path(str);
	if (path)
	{
		if (ft_strcmp(path, "~") == 0)
		{
			free (path);
			change_to_home(shell);
		}
		else if (ft_strcmp(path, "-") == 0)
		{
			oldpwd = put_in(shell->oldpwd);
			free(path);
			printf ("%s \n", oldpwd);
			return (oldpwd);
		}
		else
			return (path);
	}
	return (NULL);
}

void	ft_cd(t_linux *shell, char **str)
{
	char	*path;
	char	*pwd;

	path = what_path(shell, str);
	if (path != NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			if (chdir(path) != 0)
				perror("chdir");
			else
			{
				if (shell->oldpwd != NULL)
					s_free(&shell->oldpwd);
				shell->oldpwd = put_in(pwd);
				g_sign = 0;
			}
			free(path);
			free(pwd);
		}
		else
			error_cd("i'm in the middle of nowere");
	}
}
