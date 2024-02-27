/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammirat <aammirat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:26:20 by aammirat          #+#    #+#             */
/*   Updated: 2024/02/23 14:31:48 by aammirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	quotes_check_parse(char c, int	*quotes)
{
	int	newquotes;

	newquotes = *quotes;
	if (c == '\'' && *quotes == 0)
		newquotes = 1;
	else if (c == '\"' && *quotes == 0)
		newquotes = 2;
	else if (c == '\'' && *quotes == 1)
		newquotes = 0;
	else if (c == '\"' && *quotes == 2)
		newquotes = 0;
	*quotes = newquotes;
}

int	token_repetition(char *str, char last_token, int i, int quotes)
{
	int		count;

	count = 0;
	last_token = '\0';
	while (str[++i])
	{
		quotes_check_parse(str[i], &quotes);
		if (quotes == 0)
		{
			if (ft_strchr("<>", str[i]) != NULL)
			{
				if (last_token != '\0' && last_token != str[i])
					return (EXIT_FAILURE);
				last_token = str[i];
				count++;
			}
			else if (count != 0 && str[i] == ' ')
				count++;
			else
				count = reset_token(&last_token);
			if (count > 4 && ft_strchr("<>", str[i]) != NULL)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	preliminary(char **entry, int i)
{
	int	quotes;

	quotes = 0;
	if (is_str(*entry, is_white_space) || is_str(*entry, is_special_token))
		return (EXIT_FAILURE);
	while ((*entry)[++i])
	{
		quotes_check_parse((*entry)[i], &quotes);
		if (quotes == 0)
		{
			i += str_edit_quotes(entry, "\t", " ", i);
			i += str_edit_quotes(entry, "\n", " ", i);
			i += str_edit_quotes(entry, "\v", " ", i);
			i += str_edit_quotes(entry, "\r", " ", i);
			i += str_edit_quotes(entry, "<", " < ", i);
			i += str_edit_quotes(entry, ">", " > ", i);
		}
	}
	return (EXIT_SUCCESS);
}

char	**split_pipeline(char *cmd_in)
{
	char	**tab;
	char	*temp;

	temp = NULL;
	temp = ft_strtrim(cmd_in, " \n\v\r\t");
	if (check_unclosed_quotes(temp))
		return (err_custom(1, "unclosed quotes", 1), s_free(&temp), NULL);
	if (temp[0] == '|')
		return (err_parse_token(1), s_free(&temp), NULL);
	if (preliminary(&temp, -1) == EXIT_FAILURE)
		return (err_parse_token(1), s_free(&temp), NULL);
	if (token_repetition(temp, '\0', -1, 0))
		return (err_parse_token(1), s_free(&temp), NULL);
	str_edit(&temp, "|", " | ");
	tab = multisplit(temp, "|");
	if (is_tab(tab, is_white_space) || is_tab(tab, is_special_token))
	{
		free_tab(tab, tablen(tab));
		return (err_parse_token(1), s_free(&temp), NULL);
	}
	s_free(&temp);
	return (tab);
}

void	parse(t_linux *shell)
{
	t_cmd	*command;
	char	*raw_prompt;

	command = shell->head;
	raw_prompt = shell->input;
	if (!raw_prompt || !raw_prompt[0] || is_str(raw_prompt, is_white_space))
		return ;
	add_history(raw_prompt);
	shell->token = split_pipeline(raw_prompt);
	if (!shell->token)
		return ;
	command = build_commands(shell->head, shell->token, shell);
	launch_command(shell, NULL, shell->head->next);
	create_signal();
	free_tab(shell->token, tablen(shell->token));
	cmd_free_list(shell->head);
}
