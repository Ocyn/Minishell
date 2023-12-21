/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/21 04:17:54 by jcuzin           ###   ########.fr       */
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

typedef struct s_linux{
	char	*command;
	char	**history;
	char	**envi;
	int		nb_history;
	int		end;
}	t_linux;

void	structing(t_linux *shell);
int		ft_strlen(char *str);
void	parse(char *str, t_linux *shell);
char	*put_in(char *str);
void	add_histori(char *str, t_linux *shell);
void	bin_command(t_linux *shell);
int		ft_memcmp(char *str, char *des);
char	**ft_split(char *s, char c);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	ft_pwd(void);
int		is_built(t_linux *shell);
void	ft_cd(char *str);
int		is_same(char *str, char *cmp);
void	ft_exit(t_linux *shell);
void	free_all(t_linux *shell);
void	ft_env(t_linux *shell);
void	ft_echo(t_linux *shell);
void	ft_unset(t_linux *shell);
void	ft_export(t_linux *shell);

#endif
