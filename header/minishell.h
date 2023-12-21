/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/21 23:04:36 by jcuzin           ###   ########.fr       */
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

typedef struct s_linux
{
	char	*command;
	char	**history;
	char	**envi;
	int		nb_history;
	int		end;
}			t_linux;

void		db_debug(t_linux *sys_l, void *memm1, void **memm2);

void		struct_init(t_linux *shell, int a_nb, char **a_s, char **genv);
void		parse(char *str, t_linux *shell);
void		bin_command(t_linux *shell);
void		history_add(char *str, t_linux *shell);
int			is_builtin(t_linux *shell);

int			nav_maincore(t_linux *data, char *cmd_in);

char		**ft_split(char *s, char c);
char		*put_in(char *str);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		*s_malloc(unsigned long size);

void		s_free(void **ptr_memory);
void		free_all(t_linux *shell);
size_t		ft_strlen(char *str);
int			is_same(char *str, char *cmp);
int			ft_memcmp(char *str, char *des);

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
