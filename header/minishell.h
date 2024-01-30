t/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ocyn <ocyn@student.42.fr>				  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/20 10:59:46 by aammirat		  #+#	#+#			 */
/*   Updated: 2024/01/17 12:52:56 by ocyn			 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib.h"
# include "define_structs.h"
# include "define_syntax.h"
# include "functions_docs.h"

extern int      g_sign;

void		db_debug(void);
void		db_print_custom_font(char *message, char *font_effect);
void		db_tabstr_display(char **tab, char *message, int highlight);
void		db_display_list(t_cmd *list, char *message);

void		get_signal(t_linux *ssystem, void (*action)(int));
void		ctrl_c(int sig, siginfo_t *inf, void *gain);
void		ctrl_slash(int sig, siginfo_t *inf, void *gain);
void		nothing(int sig, siginfo_t *inf, void *gain);

char		*prompt_tuning(char *name, char *suffix, char *profile);

void		read_prompt(t_linux *ssystem, char *exit, void (*pa)(t_linux *));
void		init_struct(t_linux *shell);
t_redi		init_redi(void);

char		*whos_the_nearest_between(char *thisguy, char *thatdude, char *str);
int			is_builtin(char *cmd_in, t_linux *shell);
int			white_space(const char seek);
int			is_empty(char *str);
int			heredoc_check(const char **token, int index, int *checker);
int			str_occur(const char *src, const char *seek);
int			special_char(char *seek, int mode);

void		parse(t_linux *shell);
char		**split_command(const char *s, char c);

t_cmd		*build_commands(t_cmd *command, char **all_token);

char		**get_heredoc(char *src);

void		launch_command(t_linux *shell);
t_cmd		*fd_redirection(t_cmd *command, char **token);
char		*get_path(char *command, char **env);
char		*put_in(char *str);
int			set_infile(char *file);
int			set_outfile(char *file, int overwrite);

t_cmd		*cmd_add_unit(t_cmd *cmd);
void		cmd_init(t_cmd *cmd);
void		cmd_rm_unit(t_cmd *cmd);
void		*cmd_free_list(t_cmd *cmd);
int			list_len(t_cmd list);

t_lst		*lst_add(t_lst *last);
int			lst_len(t_lst list);
void		list_init(t_lst *lst);
void		lst_rm(t_lst *list);
void		*lst_free_list(t_lst *lst);

int			find_str_in_str(const char *src, const char *seek);
int			find_str_in_tab(int strict_mode, char *find, char **tab);
int			ft_strcmp(char *s1, char *s2);

void		cut_and_paste(void **cut, void **paste, size_t sizeof_cut);
int			skip_until(char **tab, int mode, int (*stop)(char *, int));
char		**tab_dup(char **token_tab, int token_len);
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
void		ft_cd(t_linux *shell, char **str);
void		ft_exit(t_linux *shell);
void		ft_env(t_linux *shell);
void		ft_echo(char **str);
void		ft_unset(t_linux *shell, char *src);
void		ft_export(t_linux *shell);
void		change_oldpwd(t_linux *shell);
/**
 * @file very_sure.c
 * @brief An experimental version of the secured memory handle overlay.  
 * The major difference is that the data are store in a struct
 * filled of the variable informations, like their allocation state.
 * 
 * @param data The data in the experimental s_data format.
 * @param size Set a positive integer to malloc SIZE bytes at data 
 * | Set to 0 to free the data.
 */
void		very_sure(t_sdata *data, unsigned long size);

void		change_env(t_linux *shell, char **env);
int			is_space(char c);
void		free_env(t_env *env);

void		exit_end(int launch, t_linux *shell);
void		exit_forkfailure(int launch, t_linux *shell, int *pip);
void		exit_prompt(int launch, t_linux *shell);
int			weird_cmp(char *str, char *cmp);
int			weird_cmp_export(char *str, char *cmp);
void		total_free(t_env *chain);
char		*get_var(t_env *env, char *str);
void		create_signal(void *c);

#endif
