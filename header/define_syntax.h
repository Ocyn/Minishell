/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_syntax.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 05:34:19 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/07 06:43:19 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_SYNTAX_H
# define DEFINE_SYNTAX_H

//	Special Characters part
# define EMPTY_CMD 					-1
# define SINGLE_CMD 				 0
# define PIPE_CMD 					'|'
# define INFILE_CMD 				'<'
# define OUTFILE_CMD 				'>'
# define HEREDOC 					6060
# define OUTFILE_ADDER				6262
# define DOLLARSIGN_CMD 			'$'
# define UNDEFINED_CMD 				99

# define SIMPLEQUOTE 				'\''
# define DOUBLEQUOTE 				'\"'

//	Font part
# define FONT_RESET 			"\033[0m"
# define MY_CUSTOM_PROMPT		"\e[1m\e[48;5;234m\e[38;5;105m"
# define __VALID_FREED			"\e[1m\e[4m\e[32mDONE\033[0m"
# define __INVALID_FREED		"\e[1m\e[4m\e[31mERROR\033[0m"
# define HIGHLIGHT_TEXT			"\e[7m\e[1m\e[4m"

//		Font Color
# define FONT_COLOR_BLACK		"\e[30m"
# define FONT_COLOR_RED			"\e[31m"
# define FONT_COLOR_GREEN		"\e[32m"
# define FONT_COLOR_BROWN		"\e[33m"
# define FONT_COLOR_BLUE		"\e[34m"
# define FONT_COLOR_PURPLE		"\e[38;5;105m"
# define FONT_COLOR_CYAN		"\e[36m"
# define FONT_COLOR_LIGHT_GRAY	"\e[37m"

//		Font Effect
# define FONT_EFFECT_BOLD		"\e[1m"
# define FONT_EFFECT_BLINK		"\e[5m"
# define FONT_EFFECT_UNDERLINE	"\e[4m"
# define FONT_EFFECT_REVERSE	"\e[7m"

//		BND (Background)
# define BND_DARK_GRAY			"\e[48;5;234m"
# define BND_LIGHT_RED			"\e[1;41m"
# define BND_LIGHT_GREEN		"\e[1;42m"
# define BND_YELLOW				"\e[1;43m"
# define BND_LIGHT_BLUE			"\e[1;44m"
# define BND_LIGHT_PURPLE		"\e[1;45m"
# define BND_LIGHT_CYAN			"\e[1;46m"
# define BND_WHITE				"\e[1;47m"

//		Font define shortcuts
# define FC_RED					FONT_COLOR_RED	
# define FC_GRE					FONT_COLOR_GREEN
# define FC_BRO					FONT_COLOR_BROWN
# define FC_BLU					FONT_COLOR_BLUE
# define FC_PUR					FONT_COLOR_PURPLE
# define FC_CYA					FONT_COLOR_CYAN
# define FC_GRA					FONT_COLOR_LIGHT_GRAY

# define FE_BOL					FONT_EFFECT_BOLD
# define FE_UND					FONT_EFFECT_UNDERLINE
# define FE_REV					FONT_EFFECT_REVERSE

# define BN_RED					BND_LIGHT_RED
# define BN_GRE					BND_LIGHT_GREEN
# define BN_BLU					BND_LIGHT_BLUE
# define BN_YEL					BND_YELLOW
# define BN_PUR					BND_LIGHT_PURPLE
# define BN_WHI					BND_WHITE
# define BN_CYA					BND_LIGHT_CYAN
# define BN_GRA					BND_DARK_GRAY

# define FRR					FONT_RESET

#endif
