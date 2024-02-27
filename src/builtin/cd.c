/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:08:13 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/23 11:51:16 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	error_cd(char *str)
{
	ft_putstr_fd (str, 2);
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
	if (home != NULL)
	{
		if (chdir(home) != 0)
			error_cd("minishell: cd: HOME not set correctly\n");
		else
		{
			if (pwd)
			{
				if (shell->oldpwd)
					s_free(&shell->oldpwd);
				shell->oldpwd = put_in(pwd);
				free(pwd);
			}
			g_sign = 0;
		}
		s_free(&home);
	}
	else
		error_cd("minishell: cd: HOME not set\n");
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
		if (chdir(path) != 0)
			error_cd("path not fond\n");
		else
		{
			if (pwd)
			{
				if (shell->oldpwd != NULL)
					s_free(&shell->oldpwd);
				shell->oldpwd = put_in(pwd);
			}
			g_sign = 0;
		}
		free(path);
		free(pwd);
	}
}
