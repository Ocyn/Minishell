/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:00:00 by jcuzin            #+#    #+#             */
/*   Updated: 2024/02/20 18:04:11 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_STRUCTS_H
# define DEFINE_STRUCTS_H

extern int	g_sign;

typedef struct s_lst
{
	int				id;
	char			*data;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_metadatas
{
	char			*sraw;
	char			**raw;
	char			**exec_cmd;
	int				infile;
	int				outfile;
}					t_metadatas;

typedef struct s_cmd
{
	int				id;
	t_metadatas		meta;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_linux
{
	t_cmd				*head;
	t_cmd				*command;
	char				*input;
	char				*prompt;
	int					count_cmd;
	char				**envi;
	t_env				*env;
	char				**token;
	int					end;
	char				*oldpwd;
}			t_linux;

#endif
