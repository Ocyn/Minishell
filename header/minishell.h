/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/25 21:35:17 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include "lib.h"

# define UNKNOWN_CMD 0
# define SINGLE_CMD 1
# define PIPE_CMD 2
# define INFILE_CMD 3
# define OUTFILE_CMD 4
# define HEREDOC_CMD 5
# define ENV_CMD 6
# define UNDEFINED_CMD 99

typedef struct s_execve
{
	char			**full;
	char			*one;
	char			*path;
	int				arg_n;
}					t_execve;

typedef struct s_cmd
{
	t_execve		*command;
	int				type;
	int				id;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_linux
{
	t_cmd	cmd;
	t_cmd	*cmd_h;
	char	*command;
	int		infile;
	int		outfile;
	char	**envi;
	char	**history;
	int		nb_history;
	int		end;
}			t_linux;

void		db_debug(t_linux *sys_l, void *memm1, void **memm2);

void		struct_init(t_linux *shell, int a_nb, char **a_s, char **genv);
void		parse(char *str, t_linux *shell);
char		*get_path(char *command, char **env);
int			is_builtin(char *cmd_in, t_linux *shell);
int			set_command(t_linux *shell);
void		exec_all(t_linux *shell);

t_cmd		*cmd_add_unit(t_cmd *cmd);
void		cmd_init(t_cmd *cmd, t_cmd *nxt, t_cmd *prv);
void		*cmd_rm_unit(t_cmd *cmd, t_cmd *head, int last, int first);
void		cmd_display_list(t_cmd *list);
void		*cmd_free_list(t_cmd *cmd);

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
