/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/29 01:38:15 by jcuzin           ###   ########.fr       */
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

# include "header_doc_en.h"

# define UNKNOWN_CMD -1
# define SINGLE_CMD 0
# define PIPE_CMD 124
# define INFILE_CMD 60
# define OUTFILE_CMD 62
# define DOLLARSIGN_CMD 36
# define ERROR_C -2
# define UNDEFINED_CMD 99

typedef struct s_execve
{
	char			*raw;
	char			**full;
	char			*one;
	char			*path;
	char			**env_var;
	int				arg_n;
}					t_execve;

typedef struct s_cmd
{
	int				id;
	t_execve		command;
	int				type;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_linux
{
	t_cmd	*head;
	char	*input;
	int		count_cmd;
	char	**envi;
	char	**history;
	int		nb_history;
	int		end;
}			t_linux;

void		db_debug(t_linux *sys_l);
void		db_tabstr_display(char **tab);

void		struct_init(t_linux *shell, int a_nb, char **a_s, char **genv);
void		parse(char *cmd_in, t_linux *shell);
char		*get_path(char *command, char **env);
int			is_builtin(char *cmd_in, t_linux *shell);

char		*extract_str(char *str, int start, int len);
int			multichecking(const char check, int mode);
int			command_pattern(const char seek);
int			white_space(const char seek);

int			set_infile(char *file);
int			set_outfile(char *file);

t_cmd		*cmd_add_unit(t_cmd *cmd);
void		cmd_init(t_cmd *cmd, char **data, int location);
void		cmd_rm_unit(t_cmd *cmd);
void		cmd_display_list(t_cmd *list);
void		*cmd_free_list(t_cmd *cmd);

int			str_occur(char *src, char *seek);
void		str_edit(char **src, char *seek, char *replace);
void		*s_malloc(unsigned long size);
void		s_free(char **ptr_memory);
void		free_tab(char **tab, int i);
int			ft_strcmp(char *s1, char *s2);
int			tablen(char **tab);

void		ft_pwd(void);
void		ft_cd(char *cmd);
void		ft_exit(t_linux *shell);
void		ft_env(t_linux *shell);
void		ft_echo(t_linux *shell);
void		ft_unset(t_linux *shell);
void		ft_export(t_linux *shell);

#endif
