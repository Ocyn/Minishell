/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 05:42:02 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include "lib.h"

typedef struct s_cmd
{
	pid_t	f_id;
	int		w_id;
	int		arg_n;
	char	**f_cmd;
	char	*path;
}			t_cmd;

typedef struct s_linux
{
	t_cmd	exe;
	char	*command;
	char	**envi;
	char	**history;
	int		nb_history;
	int		end;
}			t_linux;

void		db_debug(t_linux *sys_l, void *memm1, void **memm2);

void		struct_init(t_linux *shell, int a_nb, char **a_s, char **genv);
void		parse(char *str, t_linux *shell);
char		*get_path(char *command, char **env);
int			is_builtin(t_linux *shell);

int			nav_maincore(t_linux *data, char *cmd_in);

void		*s_malloc(unsigned long size);
void		s_free(char **ptr_memory);
void		free_tab(char **tab, int i);
int			ft_strcmp(const char *s1, const char *s2);
int			tablen(char **tab);

void		ft_pwd(void);
void		ft_cd(char *cmd);
void		ft_exit(t_linux *shell);
void		ft_env(t_linux *shell);
void		ft_echo(t_linux *shell);
void		ft_unset(t_linux *shell);
void		ft_export(t_linux *shell);


/**
 * @brief Allocate an array; init each element at 0
 * 
 * @details
 * Keep in mind that in order to be able to allocate every type variable
 * in one function, you will have to cast the calling of the function as
 * your array variable type. Example:
 * ```c
 * char *str = (char *)s_malloc(sizeof(char) * (9 + 1));
 * int *tab = (int *)s_malloc(sizeof(int) * (9 + 1));
 * ```
 * @param size (* sizeof(Your_Variable_Type))
 * @return void * [The allocated array]
 */
void		*s_malloc(unsigned long size);


/**
 * @brief Free a dynamically allocated 2D array of strings.
 *
 * This function frees the memory allocated for a 2D array of strings, along with
 * the memory allocated for each individual string.
 *
 * @param tab The 2D array of strings to be freed.
 * @param i The index of the last string in the array.
 */
void		free_tab(char **tab, int i);

/**
 * @brief Frees the memory pointed to by the given pointer and sets it to NULL.
 * 
 * @param ptr_memory A pointer to a pointer to the memory to be freed.
 */
void		s_free(char **ptr_memory);

#endif
