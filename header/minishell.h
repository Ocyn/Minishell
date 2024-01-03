/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/03 06:09:50 by jcuzin           ###   ########.fr       */
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
	t_cmd	*command;
	char	*input;
	char	*prompt;
	int		count_cmd;
	char	**envi;
	char	**p_set;
	int		end;
}			t_linux;

void		db_debug(void);
void		db_tabstr_display(char **tab);
void		db_display_list(t_cmd *list);


char		*prompt_tuning(char *name, char *suffix, char *profile);

void		read_prompt(t_linux *ssystem, char *exit, void (*pa)(t_linux *));
void		struct_init(t_linux *shell);

char		*whos_the_nearest_between(char *thisguy, char *thatdude, char *str);
int			is_builtin(char *cmd_in, t_linux *shell);
int			white_space(const char seek);
int			is_empty(char *str);
int			heredoc_check(const char **token, int index, int *checker);
int			command_pattern(const char *seek);

void		parse(t_linux *shell);
char		**split_command(const char *s, char c);

t_cmd		*build_commands(t_cmd *command, const char **token);
char		**get_command_args(const char **tab, int *heredoc);
t_cmd		*chk_infile(t_cmd *cmd, int *index, const char **token);

char		**new_heredoc(char *src);
char		**heredocument(char *delim, char **src, int start, char **remain);

void		launch_command(t_linux *shell);
t_cmd		*fd_redirection(t_cmd *command, char **token);
char		*get_path(char *command, char **env);
int			set_infile(char *file);
int			set_outfile(char *file);

t_cmd		*cmd_add_unit(t_cmd *cmd);
void		cmd_init(t_cmd *cmd, char **data, int location);
void		cmd_rm_unit(t_cmd *cmd);
void		*cmd_free_list(t_cmd *cmd);

int			find_str_in_str(const char *src, const char *seek);
int			find_str_in_tab(int strict_mode, char *find, char **tab);
int			ft_strcmp(char *s1, char *s2);

void		cut_and_paste(void **cut, void **paste, size_t sizeof_cut);
char		*tab_to_str(char **tab, int add_sep, int do_free_after_join);
void		whitespaces_to_space(char **entry);
void		str_edit(char **src, char *seek, char *replace);
void		*s_malloc(unsigned long size);
void		s_free(char **ptr_memory);
void		free_tab(char **tab, int i);
int			ft_strcat(char *dest, char *src);
int			tablen(char **tab);

void		ft_pwd(void);
void		ft_cd(char *cmd);
void		ft_exit(t_linux *shell);
void		ft_env(t_linux *shell);
void		ft_echo(t_linux *shell);
void		ft_unset(t_linux *shell);
void		ft_export(t_linux *shell);

#endif
