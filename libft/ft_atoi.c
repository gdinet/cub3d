/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:46:40 by gdinet            #+#    #+#             */
/*   Updated: 2019/10/10 14:35:36 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		sign;
	int		nb;

	nb = 0;
	while (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\r')
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		nb = 10 * nb + (*str - '0');
		str++;
	}
	return (nb * sign);
}
