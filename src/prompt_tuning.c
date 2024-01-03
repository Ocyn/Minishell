/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tuning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 04:31:34 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/03 04:05:13 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "../header/text_codes.h"

static char	*background_code(char *color)
{
	char	*code;

	if (!ft_strcmp(color, "RED"))
		code = ft_strdup(BN_RED);
	else if (!ft_strcmp(color, "GRE"))
		code = ft_strdup(BN_GRE);
	else if (!ft_strcmp(color, "BLU"))
		code = ft_strdup(BN_BLU);
	else if (!ft_strcmp(color, "YEL"))
		code = ft_strdup(BN_YEL);
	else if (!ft_strcmp(color, "PUR"))
		code = ft_strdup(BN_PUR);
	else if (!ft_strcmp(color, "WHI"))
		code = ft_strdup(BN_WHI);
	else if (!ft_strcmp(color, "CYA"))
		code = ft_strdup(BN_CYA);
	else if (!ft_strcmp(color, "GRA"))
		code = ft_strdup(BN_GRA);
	else
		code = NULL;
	return (code);
}

static char	*font_code(char *color)
{
	char	*code;

	if (!ft_strcmp(color, "GRA"))
		code = ft_strdup(FC_GRA);
	else if (!ft_strcmp(color, "RED"))
		code = ft_strdup(FC_RED);
	else if (!ft_strcmp(color, "GRE"))
		code = ft_strdup(FC_GRE);
	else if (!ft_strcmp(color, "BRO"))
		code = ft_strdup(FC_BRO);
	else if (!ft_strcmp(color, "BLU"))
		code = ft_strdup(FC_BLU);
	else if (!ft_strcmp(color, "PUR"))
		code = ft_strdup(FC_PUR);
	else if (!ft_strcmp(color, "CYA"))
		code = ft_strdup(FC_CYA);
	else if (!ft_strcmp(color, "BOL"))
		code = ft_strdup(FE_BOL);
	else if (!ft_strcmp(color, "UND"))
		code = ft_strdup(FE_UND);
	else if (!ft_strcmp(color, "REV"))
		code = ft_strdup(FE_REV);
	else
		code = NULL;
	return (code);
}

static char	*apply_setting(char *entry, char **type)
{
	char	*applied;
	char	*code;

	applied = NULL;
	code = NULL;
	if (type[2] || ft_strlen(type[0]) != 2 || ft_strlen(type[1]) != 3)
		return (free_tab(type, tablen(type)), entry);
	if (!ft_strcmp(type[0], "FC") || !ft_strcmp(type[0], "FE"))
		code = font_code(type[1]);
	else if (!ft_strcmp(type[0], "BN"))
		code = background_code(type[1]);
	else
		return (NULL);
	applied = ft_strjoin(code, entry);
	if (!applied)
		return (NULL);
	s_free(&entry);
	s_free(&code);
	free_tab(type, tablen(type));
	return (applied);
}

static int	init_all(char ***settings, char *entry, char **suffix)
{
	char	*temp;

	temp = NULL;
	if (!entry)
		return (0);
	*settings = ft_split(entry, ' ');
	if (!*settings || !*settings[0])
		return (0);
	*suffix = ft_strjoin(" "FONT_RESET" ", *suffix);
	cut_and_paste((void **)suffix, (void **)&temp, ft_strlen(*suffix) + 1);
	*suffix = ft_strjoin(temp, " ");
	s_free(&temp);
	return (1);
}

char	*prompt_tuning(char *name, char *suffix, char *profile)
{
	char	*prompt;
	char	**settings;
	int		set_index;

	prompt = NULL;
	settings = NULL;
	set_index = -1;
	if (!init_all(&settings, profile, &suffix))
		return (ft_strdup("> "));
	prompt = ft_strjoin(" ", name);
	printf("\nPrompt Tuning \n\tPrompt: [%s]\n\tSuffix: [%s]\n\tSettings: ", prompt, suffix);
	db_tabstr_display(settings);
	printf("\n\n");
	while (name && settings[++set_index])
		prompt = apply_setting(prompt, ft_split(settings[set_index], '_'));
	free_tab(settings, tablen(settings));
	profile = NULL;
	cut_and_paste((void **)&prompt, (void **)&profile \
	, sizeof(char) * ft_strlen(prompt) + 1);
	prompt = ft_strjoin(profile, suffix);
	s_free(&profile);
	s_free(&suffix);
	printf("\n\n\tNew Prompt: [%s]\n\n\n", prompt);
	return (prompt);
}
