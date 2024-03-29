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

char		*prompt_tuning(char *name, char *suffix, char *profile);

void		read_prompt(t_linux *ssystem, char *exit, void (*pa)(t_linux *));
void		init_struct(t_linux *shell);
void		cmd_init(t_cmd *cmd);

char		*whos_the_nearest_between(char *thisguy, char *thatdude, char *str);
char		*ft_strtok(char *src, char delim);
int			is_builtin(char *cmd_in, t_cmd *cmd, t_env *env, t_linux *shell);
int			is_white_space(const char seek);
int			is_special_token(const char seek);
int			is_str(char *str, int (*check)(const char));
int			is_tab(char **tab, int (*check)(const char));
int			heredoc_check(const char **token, int index, int *checker);
int			str_occur(const char *src, const char *seek);

void		parse(t_linux *shell);
char		**multisplit(const char *s, char *keys);
t_cmd		*build_commands(t_cmd *command, char **tokens, t_linux *envv);
t_lst		*get_redirection(t_lst *list, int *redi, t_linux *env);
void		launch_command(t_linux *shell, t_cmd *command, t_cmd *start);
char		*get_file_name(char *token, char type);
char		*get_path(char *command, t_env *env);
char		*put_in(char *str);
char		**get_heredoc(char *src);
int			set_infile(t_lst *file, int heredoc, int oldfd, t_linux *env);
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
int			str_edit_quotes(char **src, char *seek, char *replace, int i);
int			ft_strcat(char *dest, char *src);
int			tablen(char **tab);
int			str_occur(const char *src, const char *seek);

void		*s_malloc(unsigned long size);
void		s_free(char **ptr_memory);
void		free_tab(char **tab, int i);
void		quotes_check_parse(char c, int	*quotes);
int			reset_token(char	*last_token);

int			cmd_len(t_cmd *cmd);
void		ft_pwd(void);
void		ft_cd(t_linux *shell, char **str);
void		ft_exit(t_cmd *cmd, t_linux *shell);
void		ft_env(t_env *env);
void		ft_echo(char **str);
void		ft_unset(t_cmd *cmd, t_env *env, char *src);
void		ft_export(t_cmd *cmd, t_env *env);
void		change_oldpwd(t_linux *shell);

char		*get_var(t_env *env, char *str);
void		change_env(t_linux *shell, char **env);
int			is_space(char c);
void		free_env(t_env *env);
void		basic_env(t_env *env);
void		change_env_arg(char **tab, t_env *env);
char		*path_not_found(char *str);

int			err_custom(int launch, char *message, int sig);
int			err_parse_token(int launch);
int			err_perror(int launch);
int			s_close(int launch, int fd);

void		exit_end(int launch, t_linux *shell);
void		exit_forkfailure(int launch, t_linux *shell, char **path);
void		exit_fork(int sig, t_linux *shell, t_pipeline *tbl, char **path);
void		exit_prompt(int launch, t_linux *shell);

int			weird_cmp(char *str, char *cmp);
int			weird_cmp_export(char *str, char *cmp);
void		total_free(t_env *chain);

t_lst		*lst_add_fragment_str(t_lst *last, char *str, int i, int j);
void		create_signal(void);
void		ctrl_c(int sig, siginfo_t *inf, void *gain);
void		let_signal_through(void);
int			check_unclosed_quotes(char *tab);
char		*lst_to_char(t_lst *lst);

void		ampute_quotes(char **tab);
void		change_var_sign(char **str);

void		s_dup(int fdin, int fdout, int fd_bonus);
int			is_expand(char **list);

void		change_ret_signal(int c, int id);
int			pipe_tool(int *piipe, int initorclose);
int			heredocument(t_lst *delim, int expand, t_linux *env);
int			len_after_ampute(char *tab);
char		*final_quotes(char *new, char *tab);

#endif
