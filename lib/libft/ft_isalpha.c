/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcuzin <jcuzin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:55:50 by jcuzin            #+#    #+#             */
/*   Updated: 2022/12/06 16:54:51 by jcuzin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int input)
{
	if ((input >= 65 && input <= 90) || (input >= 97 && input <= 122))
		return (1);
	else
		return (0);
}
