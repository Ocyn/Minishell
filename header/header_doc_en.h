/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_doc_en.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 05:18:34 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/26 06:30:57 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_DOC_EN_H
# define HEADER_DOC_EN_H

/**
 * @brief Structure representing a Linux shell.
 * 
 * This structure contains information about a Linux shell, 
 * including the command, command history, 
 * environment variables, and other related data.
 */
struct	s_linux;

/**
 * @struct t_cmd
 * @brief Structure representing a command in a minishell.
 * 
 * The t_cmd structure contains information about the command to be executed.
 * It includes an ID, a command to execute, a type, 
 * an input file descriptor, an output file descriptor, 
 * and pointers to the next and previous commands in a linked list.
 */
struct	s_cmd;

/**
 * @struct s_execve
 * @brief Structure representing the key parameters of the command to be executed
 * using execv().
 * 
 * This structure contains the following members:
 * - pattern: A string representing the pattern of the command.
 * - full: An array of strings representing the complete command
 * with arguments.
 * - one: A string representing the command without arguments.
 * - path: A string representing the path
 * to the executable of the command.
 * - arg_n: An integer representing the number of arguments in the command.
 */
struct	s_execve;

/**
 * @brief Checks for the presence of white space and the format of the command to be retrieved.
 * 
 * @param check The character to check.
 * @param mode The mode to determine the type of check.
 * @return int The result of the multiple checks.
 * - If mode == 1, returns the result of the command pattern check.
 * - If mode != 1, returns the result of the white space check.
 */
int			multichecking(const char check, int mode);

/**
 * @brief Checks if the given character is a white space character.
 * 
 * @param seek The character to check.
 * @return
 * Returns 1 if the character is a white space character, 0 otherwise.
 */
int			white_space(const char seek);

/**
 * @brief Allocates an array and initializes each element to 0.
 * Similar to calloc but with additional safety measures. 
 * 
 * @details
 * Do not forget to specify sizeof([...]).
 * WARNING
 * This wrapper enhances the safety of using malloc()
 * but keep in mind that making s_malloc() C-compliant while respecting
 * the 42 Norm is a different matter. So please be careful
 * when using s_malloc().
 * @param size (* sizeof(Your_Variable_Type))
 * @return void * [The allocated array]
 */
void		*s_malloc(unsigned long size);

/**
 * @brief Frees a 2D matrix of strings.
 *
 * @details
 * This function frees the memory allocated for a 2D matrix of strings,
 * as well as the memory allocated for each individual string.
 *
 * @param tab The 2D matrix of strings to free.
 * @param i The index of the last string in the array.
 */
void		free_tab(char **tab, int i);

/**
 * @brief Safely frees dynamically allocated memory.
 * 
 * @details
 * Checks the possibility of freeing the memory pointed to by the given pointer,
 * frees the pointed memory and sets it to NULL.
 * 
 * @param ptr_memory A pointer to a pointer of the memory to free.
 */
void		s_free(char **ptr_memory);

#endif
