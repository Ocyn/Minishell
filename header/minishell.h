/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 01:54:34 by jcuzin           ###   ########.fr       */
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
	char	*cmd;
	char	*path;
	char	**args;
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
void		bin_command(t_linux *shell);
char		*get_path(char *command, char **env);
int			is_builtin(t_linux *shell);

int			nav_maincore(t_linux *data, char *cmd_in);

void		*s_malloc(unsigned long size);
void		s_free(void **ptr_memory);
void		free_tab(void **ptr_tab, size_t i);
int			ft_strcmp(const char *s1, const char *s2);

void		ft_pwd(void);
void		ft_cd(char *cmd);
void		ft_exit(t_linux *shell);
void		ft_env(t_linux *shell);
void		ft_echo(t_linux *shell);
void		ft_unset(t_linux *shell);
void		ft_export(t_linux *shell);



/**
 * @brief Safely free a pointer and set it to NULL
 * 
 * @details
 * This function provides a safer alternative to the standard free() function.
 * It checks if the pointer is not NULL before freeing it, avoiding invalid reads,
 * invalid frees, and double frees. After freeing the pointer, it sets it to NULL.
 * ```c
 * // Using free()
 * char *str = malloc(sizeof(char) * 10);
 * strcpy(str, "Hello");
 * free(str);
 * printf("%s\n", str); // This will cause an invalid read
 * // Using s_free()
 * char *str = (char *)s_malloc(sizeof(char) * 10);
 * strcpy(str, "Hello");
 * s_free((void **)&str);
 * printf("%s\n", str); // This will print (null)
 * ```
 * @param ptr_memory [A pointer to the memory to be freed]
 * @return void
 */
void		s_free(void **ptr_memory);

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
#endif
