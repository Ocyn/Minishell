/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/21 14:42:56 by jcuzin           ###   ########.fr       */
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

typedef struct s_linux
{
	char	*command;
	char	**history;
	char	**envi;
	int		nb_history;
	int		end;
}			t_linux;

void		db_debug(t_linux *sys_l, void *memm1, void **memm2);

void		struct_init(t_linux *shell);
void		parse(char *str, t_linux *shell);
void		add_histori(char *str, t_linux *shell);
void		bin_command(t_linux *shell);
int			is_builtin(t_linux *shell);

char		**ft_split(char *s, char c);
char		*put_in(char *str);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		*s_malloc(size_t size);
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

#endif
