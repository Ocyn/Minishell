/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:59:46 by aammirat          #+#    #+#             */
/*   Updated: 2024/01/04 09:35:09 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib.h"
# include "define_structs.h"
# include "define_syntax.h"
# include "functions_docs.h"

void		db_debug(void);
void		db_tabstr_display(char **tab, char *message, int highlight);
void		db_display_list(t_cmd *list, char *message);

void		get_signal(t_linux *ssystem, void (*action)(int));

char		*prompt_tuning(char *name, char *suffix, char *profile);

void		read_prompt(t_linux *ssystem, char *exit, void (*pa)(t_linux *));
void		struct_init(t_linux *shell);

char		*whos_the_nearest_between(char *thisguy, char *thatdude, char *str);
int			is_builtin(char *cmd_in, t_linux *shell);
int			white_space(const char seek);
int			is_empty(char *str);
int			heredoc_check(const char **token, int index, int *checker);
int			str_occur(const char *src, const char *seek);
int			special_char(char *seek);

void		parse(t_linux *shell);
char		**split_command(const char *s, char c);

t_cmd		*build_commands(t_cmd *command, char **all_token);
char		**get_args(char **token);

char		**new_heredoc(char *src, int pipe_mode);

void		launch_command(t_linux *shell);
t_cmd		*fd_redirection(t_cmd *command, char **token);
char		*get_path(char *command, char **env);
int			set_infile(char *file);
int			set_outfile(char *file);

t_cmd		*cmd_add_unit(t_cmd *cmd);
void		cmd_init(t_cmd *cmd);
void		cmd_rm_unit(t_cmd *cmd);
void		*cmd_free_list(t_cmd *cmd);
int			list_len(t_cmd list);

int			find_str_in_str(const char *src, const char *seek);
int			find_str_in_tab(int strict_mode, char *find, char **tab);
int			ft_strcmp(char *s1, char *s2);

void		cut_and_paste(void **cut, void **paste, size_t sizeof_cut);
void		insert_tab_in_tab(char **insert, char ***tab, int where);
char		*tab_to_str(char **tab, int size, int add_sep, int freed);
void		whitespaces_to_space(char **entry);
char		**list_to_tab(t_cmd *list);
void		str_edit(char **src, char *seek, char *replace);
int			ft_strcat(char *dest, char *src);
int			tablen(char **tab);

void		*s_malloc(unsigned long size);
void		s_free(char **ptr_memory);
void		free_tab(char **tab, int i);

void		ft_pwd(void);
void		ft_cd(char *cmd);
void		ft_exit(t_linux *shell);
void		ft_env(t_linux *shell);
void		ft_echo(t_linux *shell);
void		ft_unset(t_linux *shell);
void		ft_export(t_linux *shell);

/**
 * @file very_sure.c
 * @brief An experimental version of the secured memory handle overlay.  
 * The major difference is that the data are store in a struct
 * filled of the variable informations, like their allocation state.
 * 
 * @param data The data in the experimental s_data format.
 * @param size Put a size to malloc size at data | Put 0 to free the data.
 */
void		very_sure(t_sdata *data, unsigned long size);

#endif
