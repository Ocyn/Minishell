/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_doc_fr.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 05:18:34 by jcuzin            #+#    #+#             */
/*   Updated: 2023/12/26 06:29:05 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_DOC_FR_H
# define HEADER_DOC_FR_H

/**
 * @brief Structure représentant un shell Linux.
 * 
 * Cette structure contient des informations sur un shell Linux, 
 * y compris la commande, l'historique des commandes, 
 * les variables d'environnement et d'autres données connexes.
 */
struct	s_linux;

/**
 * @struct t_cmd
 * @brief Structure représentant une commande dans un minishell.
 * 
 * La structure t_cmd contient les informations de la commande a executer.
 * Elle inclut un ID, une commande à exécuter, un type, 
 * un descripteur de fichier d'entrée, un descripteur de fichier de sortie, 
 * et des pointeurs vers les commandes suivantes 
 * et précédentes dans une liste chaînée.
 */
struct	s_cmd;

/**
 * @struct s_execve
 * @brief Structure représentant les paramètres clé de la commande a executer
 * en utilisant execv().
 * 
 * Cette structure contient les membres suivants:
 * - pattern: Une chaîne de caractères représentant le motif de la commande.
 * - full: Un tableau de chaînes de caractères représentant la commande complète
 * avec les arguments.
 * - one: Une chaîne de caractères représentant la commande sans arguments.
 * - path: Une chaîne de caractères représentant le chemin
 * vers l'exécutable de la commande.
 * - arg_n: Un entier représentant le nombre d'arguments dans la commande.
 */
struct	s_execve;

/**
 * @brief Permet de verifier en une fois la presence de white_space
 * et le format de la commande a recuperer.
 * 
 * @param check Le caractère à vérifier.
 * @param mode Le mode pour déterminer le type de vérification.
 * @return int Le résultat de la vérification multiple.
 *- Si mode == 1, renvoie le résultat de la vérification du motif de la commande.
 *- Si mode != 1, renvoie le résultat de la vérification de l'espace blanc.
 */
int			multichecking(const char check, int mode);

/**
 * @brief Vérifie si le caractère donné est un caractère d'espace blanc.
 * 
 * @param seek Le caractère à vérifier.
 * @return
 * Renvoie 1 si le caractère est un caractère d'espace blanc, 0 sinon.
 */
int			white_space(const char seek);

/**
 * @brief Alloue un tableau et initialise chaque élément à 0.
 * Comme le ferait calloc mais avec d'avantages de securités. 
 * 
 * @details
 * Ne pas oublier de preciser sizeof([...]).
 * AVERTISSEMENT
 * Cette surcouche renforce la securité de l'utilisation de malloc()
 * mais gardez a l'esprit que rendre s_malloc() en C tout en respectant
 * la Norme 42 est une tout autre affaire. Veuillez donc faire attention
 * malgré tout lors de l'utilisation de s_malloc().
 * @param size (* sizeof(Votre_Type_Variable))
 * @return void * [Le tableau alloué]
 */
void		*s_malloc(unsigned long size);

/**
 * @brief Libère une matrice 2D de strings.
 *
 * @details
 * Cette fonction libère la mémoire allouée pour une matrice 2D de strings,
 * ainsi que la mémoire allouée pour chaque chaîne individuelle.
 *
 * @param tab La matrice 2D de chaînes de caractères à libérer.
 * @param i L'index de la dernière chaîne dans le tableau.
 */
void		free_tab(char **tab, int i);

/**
 * @brief Libere avec plus de securité une memoire allouée dynamiquement.
 * 
 * @details
 * Verifie la possibilité de liberer la memoire pointé par le pointeur donné,
 * libère la mémoire pointée et le met à NULL.
 * 
 * @param ptr_memory Un pointeur vers un pointeur de la mémoire à libérer.
 */
void		s_free(char **ptr_memory);

#endif
