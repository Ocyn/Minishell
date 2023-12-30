/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2023/12/30 14:42:45 by jcuzin           ###   ########.fr       */
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

# include "header_doc_fr.h"

# define FONT_EFFECT_BOLD			"\e[1m"
# define FONT_EFFECT_BLINK			"\e[5m"
# define FONT_BACK_COLOR_BLACK		"\e[48;5;234m"
# define FONT_COLOR_PURPLE 			"\e[38;5;105m"
# define FONT_BACK_COLOR_RESET 		"\e[0m"
# define FONT_RESET 				"\033[0m"

# define CUSTOM_PROMPT				"\e[1m\e[48;5;234m\e[38;5;105m"

# define EMPTY_CMD 					-1
# define SINGLE_CMD 				 0
# define PIPE_CMD 					'|'
# define INFILE_CMD 				'<'
# define OUTFILE_CMD 				'>'
# define HEREDOC 					6060
# define OUTFILE_ADDER				6262
# define DOLLARSIGN_CMD 			'$'
# define ERROR_C 					-2
# define UNDEFINED_CMD 				99

# define SIMPLEQUOTE 				'\''
# define DOUBLEQUOTE 				'\"'

typedef struct s_execve
{
	char			*raw;
	char			**full;
	char			*one;
	char			**env_var;
}					t_execve;

typedef struct s_cmd
{
	int				id;
	t_execve		command;
	int				type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_linux
{
	t_cmd	*head;
	char	*input;
	int		count_cmd;
	char	**envi;
	int		end;
}			t_linux;

void		db_debug(t_linux *sys_l);
void		db_tabstr_display(char **tab);
void		db_display_list(t_cmd *list);

void		struct_init(t_linux *shell, int a_nb, char **a_s, char **genv);

void		parse(char *cmd_in, t_linux *shell);
char		**split_command(const char *s, char c);
t_cmd		*build_commands(t_cmd *command, const char **token);
int			is_builtin(char *cmd_in, t_linux *shell);
int			is_empty(char *str);
char		*tab_to_str(char **tab, int add_sep, int do_free_after_join);
int			ft_strcat(char *dest, char *src);
void		whitespaces_to_space(char **entry);
int			command_pattern(const char *seek);
int			white_space(const char seek);

t_cmd		*heredocument(t_cmd *cmd, char *delimiter);

void		launch_command(t_linux *shell);
t_cmd		*fd_redirection(t_cmd *command, char **token);
char		*get_path(char *command, char **env);
int			set_infile(char *file);
int			set_outfile(char *file);

t_cmd		*cmd_add_unit(t_cmd *cmd);
void		cmd_init(t_cmd *cmd, char **data, int location);
void		cmd_rm_unit(t_cmd *cmd);
void		*cmd_free_list(t_cmd *cmd);

int			str_occur(const char *src, const char *seek);
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
