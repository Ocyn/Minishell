/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jcuzin <jcuzin@student.42.fr>				  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/20 10:59:46 by aammirat		  #+#	#+#			 */
/*   Updated: 2024/01/17 12:52:56 by jcuzin			 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib.h"
# include "define_structs.h"
# include "define_syntax.h"
# include "functions_docs.h"

void		db_debug(void);
void		db_printf(char *message, char *font_effect);
void		db_tabstr_display(char **tab, char *message, int highlight);
void		db_display_list(t_lst *list, char *message, int alldata);
void		db_display_list_cmd(t_cmd *list, char *message, int alldata);
int			db_close(int fd);
void		*db_cmd_free_list(t_cmd *cmd);
void		*db_lst_free_list(t_lst *lst, char *title);

char		*prompt_tuning(char *name, char *suffix, char *profile);

void		read_prompt(t_linux *ssystem, char *exit, void (*pa)(t_linux *));
void		init_struct(t_linux *shell);
void		cmd_init(t_cmd *cmd);

char		*whos_the_nearest_between(char *thisguy, char *thatdude, char *str);
char		*ft_strtok(char *src, char delim);
int			is_builtin(char *cmd_in, t_linux *shell);
int			is_white_space(const char seek);
int			is_special_token(const char seek);
int			is_str(char *str, int (*check)(const char));
int			is_tab(char **tab, int (*check)(const char));
int			str_occur(const char *src, const char *seek);

void		parse(t_linux *shell);
char		**multisplit(const char *s, char *keys);
t_cmd		*build_commands(t_cmd *command, char **tokens, t_env *envv);
t_lst		*get_redirection(t_lst *list, int *redi, int *err);
int			heredocument(char *delim, int expand, t_env *env);
int			pipe_tool(int *piipe, int initorclose);
void		launch_command(t_linux *shell, t_cmd *cmd);
char		*get_file_name(char *token, char type);
char		*get_path(char *command, t_env *env);
char		*put_in(char *str);
int			set_infile(char *file, int heredoc, int oldfd);
int			set_outfile(char *file, int append, int oldfd);

t_cmd		*cmd_add_unit(t_cmd *cmd);
void		cmd_init(t_cmd *cmd);
void		cmd_rm_unit(t_cmd *cmd);
void		*cmd_free_list(t_cmd *cmd);
int			list_len(t_cmd list);

t_lst		*lst_init(void);
t_lst		*lst_add(t_lst *last);
int			lst_len(t_lst *list, int fromhere);
t_lst		*lst_rm(t_lst *list);
void		*lst_free_list(t_lst *lst);
t_lst		*lst_tab_to_list(char **tab);
t_lst		*lst_go_to(t_lst *list, int firstorlast);
char		**lst_list_to_tab(t_lst *list);

int			find_str_in_str(const char *src, const char *seek);
int			find_str_in_tab(int strict_mode, char *find, char **tab);
int			find_str_in_list(t_lst *list_input, char *key);
int			how_many_occur(char *src, char *seek);
int			ft_strcmp(char *s1, char *s2);

void		cut_and_paste(void **cut, void **paste, size_t sizeof_cut);
int			skip_until_tab(char **tab, int mode, int (*stop)(char *, int));
char		**tab_dup(char **token_tab, int token_len);
void		insert_tab_in_tab(char **insert, char ***tab, int where);
char		*tab_to_str(char **tab, int size, int add_sep, int freed);
void		whitespaces_to_space(char **entry);
char		**cmd_list_to_tab(t_cmd *list);
void		str_edit(char **src, char *seek, char *replace);
void		str_edit_quotes(char **src, char *seek, char *replace);
int			ft_strcat(char *dest, char *src);
int			tablen(char **tab);

void		*s_malloc(unsigned long size);
void		s_free(char **ptr_memory);
void		free_tab(char **tab, int i);
int			s_close(int fd);

void		ft_pwd(void);
void		ft_cd(t_linux *shell, char **str);
void		ft_exit(t_linux *shell);
void		ft_env(t_linux *shell);
void		ft_echo(char **str);
void		ft_unset(t_linux *shell, char *src);
void		ft_export(t_linux *shell);
void		change_oldpwd(t_linux *shell);

char		*get_var(t_env *env, char *str);
void		change_env(t_linux *shell, char **env);
void		change_ret_signal(int c);
int			is_space(char c);
void		free_env(t_env *env);
void		basic_env(t_env *env);
void		change_env_arg(char **tab, t_env *env);
char		*path_not_found(char *str);

int			err_custom(int launch, char *message);
int			err_perror(int launch);
int			err_parse_token(int launch);

void		exit_end(int launch, t_linux *shell);
void		exit_forkfailure(int e_sig, t_linux *shell, int *pip, char **path);
void		exit_prompt(int launch, t_linux *shell);

int			weird_cmp(char *str, char *cmp);
int			weird_cmp_export(char *str, char *cmp);
void		total_free(t_env *chain);

void		create_signal(void);
void		ctrl_c(int sig, siginfo_t *inf, void *gain);
void		let_signal_through(void);

#endif
