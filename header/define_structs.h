/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:00:00 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 04:09:51 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_STRUCTS_H
# define DEFINE_STRUCTS_H

typedef struct s_sdata
{
	int				sstr;
	char			**str;
}					t_sdata;

typedef struct s_query
{
	int				id;
	int				start;
	int				end;
	int				boolean;
	int				index;
	int				len;
	int				range;
	char			*pattern;
	char			letter;
	char			*str;
	char			**tab;
}					t_query;

typedef struct s_execve
{
	char			*sraw;
	char			**raw;
	char			**prefixes;
	char			**args;
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

typedef struct s_lst
{
	int				id;
	void			*data;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

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

#endif
