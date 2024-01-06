/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_docs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 05:18:34 by jcuzin            #+#    #+#             */
/*   Updated: 2024/01/04 08:47:45 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_DOCS
# define FUNCTIONS_DOCS

/**
 * @brief Structure representing the data for a string.
 * 
 * This structure contains an integer and a pointer to an array of strings.
 * The integer represents the size of the array, 
 * and the pointer points to the array of strings.
 */
struct	s_sdata;

/**
 * @brief Structure representing the data for the execve command.
 * 
 * This structure contains a raw command string, 
 * an array of prefixes, an array of arguments,
 * and an array of environment variables.
 */
struct	s_execve;

/**
 * @brief Structure representing a command.
 * 
 * This structure contains an ID, a t_execve structure representing the command,
 * a type, and pointers to the next and previous commands.
 */
struct	s_cmd;

/**
 * @brief Structure representing the data for a Linux shell.
 * 
 * This structure contains pointers to the head and current command,
 * an input string, a prompt string, the count of commands,
 * arrays of environment variables and settings, and an end flag.
 * 
 */
struct	s_linux;

/**
 * @brief Checks for the presence of white space 
 * and the format of the command to be retrieved.
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
