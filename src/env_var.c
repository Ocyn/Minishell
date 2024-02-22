/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:59:33 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/21 21:38:30 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	cmp_for_env(char *str, char *cmp)
{
	int	i;

	i = 0;
	while (cmp[i])
		i++;
	if (i <= 1)
		return (0);
	i = 0;
	while (str[i] && cmp[i + 1])
	{
		if (str[i] != cmp[i + 1])
			return (0);
		i++;
	}
	if (str[i] && str[i] == '=')
		return (1);
	return (0);
}

void	expended_variable(t_lst *new, t_env *env)
{
	t_lst	*buf;
	t_env	*check;
	int		i;

	check = env;
	while (check)
	{
		buf = new;
		while (buf && buf->data)
		{
			if (buf->data[0] == '$' && ft_strncmp(buf->data, "$?", 2) \
			&& cmp_for_env(check->str, buf->data))
			{
				i = 0;
				while (check->str[i] != '=')
					i++;
				s_free(&buf->data);
				buf->data = ft_strdup(&check->str[i + 1]);
			}
			buf = buf->next;
		}
		check = check->next;
	}
}

int	is_quotes(int *i, int *j, t_lst **new, char *str)
{
	static int	quotes;

	if (j == 0 && new == NULL && str == NULL)
	{
		quotes = 0;
		return (0);
	}
	quotes_check_parse(str[(*i)], &quotes);
	if (quotes == 1)
	{
		(*new) = lst_add_fragment_str(*new, str, *j, *i);
		*j = *i;
		while (str[(*i)] && quotes == 1)
		{
			(*i)++;
			quotes_check_parse(str[(*i)], &quotes);
		}
		(*i)++;
		(*new) = lst_add_fragment_str(*new, str, *j, *i);
		*j = *i;
		return (1);
	}
	return (0);
}

t_lst	*split_var(char *str, int i, int quotes)
{
	int		j;
	t_lst	*new;
	t_lst	*start;

	j = 0;
	new = lst_init();
	start = new;
	while (str[i])
	{
		quotes = is_quotes(&i, &j, &new, str);
		if (quotes == 0 && str[i] == '$')
		{
			new = lst_add_fragment_str(new, str, j, i);
			j = i;
			i++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			new = lst_add_fragment_str(new, str, j, i);
			j = i;
		}
		else if (quotes == 0)
			i++;
	}
	new = lst_add_fragment_str(new, str, j, i);
	return (start);
}

void	change_env_arg(char **tab, t_env *env)
{
	int		i;
	t_lst	*new;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
	{
		is_quotes(0, 0, NULL, NULL);
		new = split_var(tab[i], 0, 0);
		expended_variable(new, env);
		if (new != NULL)
		{
			s_free(&tab[i]);
			tab[i] = lst_to_char(new);
			change_var_sign(&tab[i]);
		}
		if (new)
			lst_free_list(new);
	}
}
